import 'dart:async';
import 'package:flutter/material.dart';
import 'package:src/models/food/progress_semi_circle.dart';
import 'package:src/pages/chatbot.dart';
import 'package:src/models/section_title_model.dart';
import 'package:src/models/card_container_model.dart';
import 'package:src/crud/foodcrud.dart';
import 'package:src/data/food_data.dart';
import 'package:src/crud/trainingcrud.dart';
import 'package:src/data/training_data.dart';
import 'package:src/crud/profilcrud.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key, this.pageController, this.refreshSignal});

  final PageController? pageController;
  final ValueNotifier<int>? refreshSignal;

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final _foodCrud = FoodCrud();
  final _trainingCrud = TrainingCrud();
  final _profilCrud = ProfilCrud();
  NutritionData? _foodData;
  TrainingData? _trainingData;
  String _profileName = 'Vorname Nachname';
  StreamSubscription? _profilSub;
  bool _loading = true;

  @override
  void initState() {
    super.initState();
    _loadData();
    widget.refreshSignal?.addListener(_onRefreshSignal);
  }

  Future<void> _loadData() async {
    final now = DateTime.now();
    final foodFuture = _foodCrud.loadDay(now);
    final trainingFuture = _trainingCrud.loadDay(now, availableTrainingPlans);
    final profilFuture = _profilCrud.getProfil();
  
    final foodLoaded = await foodFuture;
    final trainingLoaded = await trainingFuture;
    final profilLoaded = await profilFuture;
    setState(() {
      _foodData = foodLoaded;
      _trainingData = trainingLoaded;
      _profileName = profilLoaded.name;
      _loading = false;
    });

    _profilSub ??= _profilCrud.watchProfil().listen((profil) {
      if (!mounted) return;
      setState(() => _profileName = profil.name);
    });
  }

  @override
  void dispose() {
    widget.refreshSignal?.removeListener(_onRefreshSignal);
    _profilSub?.cancel();
    super.dispose();
  }

  void _onRefreshSignal() {
    _loadData();
  }

  Future<void> refreshData() async {
    await _loadData();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Padding(
        padding: const EdgeInsets.only(left: 16.0, right: 16.0, top: 30.0),
        child: SingleChildScrollView(
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Text.rich(
                TextSpan(
                  text: 'Hallo, ',
                  style: const TextStyle(
                    fontSize: 30.0,
                    fontWeight: FontWeight.bold,
                  ),
                  children: [
                    TextSpan(
                      text: _profileName,
                      style: TextStyle(
                        fontSize: 30.0,
                        fontWeight: FontWeight.bold,
                        color: Theme.of(context).colorScheme.primary,
                      ),
                    ),
                  ],
                ),
              ),
              SizedBox(height: 25),
              Padding(
                padding: const EdgeInsets.all(8.0),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    if (_loading)
                      const Center(child: CircularProgressIndicator())
                    else ...[
                      SectionTitleModel(title: 'Heute übrige Kalorien'),
                      SizedBox(height: 20),
                      if (_foodData != null)
                        GestureDetector(
                          onTap: () {
                            widget.pageController?.animateToPage(
                              0,
                              duration: const Duration(milliseconds: 300),
                              curve: Curves.ease,
                            );
                          },
                          child: CardContainerModel(
                            context: context,
                            padding: 30.0,
                            child: _buildCalorieCircle(context, _foodData!),
                          ),
                        ),
                        SizedBox(height: 20),
                        SectionTitleModel(title: 'Heute verbrannte Kalorien'),
                        SizedBox(height: 20),
                      if (_trainingData != null)
                        GestureDetector(
                          onTap: () {
                            widget.pageController?.animateToPage(
                              2,
                              duration: const Duration(milliseconds: 300),
                              curve: Curves.ease,
                            );
                          },
                          child: CardContainerModel(
                            context: context,
                            padding: 30.0,
                            child: _buildBurnedCaloriesCircle(context, _trainingData!),
                          ),
                        )
                      else
                        GestureDetector(
                          onTap: () {
                            widget.pageController?.animateToPage(
                              2,
                              duration: const Duration(milliseconds: 300),
                              curve: Curves.ease,
                            );
                          },
                          child: CardContainerModel(
                            context: context,
                            child: Center(
                              child: Text(
                                'Wähle einen Trainingsplan aus',
                                style: TextStyle(
                                  fontSize: 14,
                                  color: Theme.of(context).colorScheme.onSurface.withAlpha(153),
                                ),
                              ),
                            ),
                          ),
                        ),
                    ]
                  ],
                ),
              ), 
            ]
          ),
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.push(context, MaterialPageRoute(builder: (context) => ChatbotPage()));
        },
        backgroundColor: Theme.of(context).colorScheme.primary,
        tooltip: 'Chatbot',
        child: Icon(Icons.smart_toy, size: 30, color: Theme.of(context).colorScheme.onPrimary),
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.startFloat,
    );
  }

  Widget _buildCalorieCircle(BuildContext context, NutritionData data) {
    double progress = (data.caloriesConsumed / data.caloriesGoal).clamp(0.0, 1.0);
    int remaining = data.caloriesGoal - data.caloriesConsumed;

    return Center(
      child: SizedBox(
        height: 100,
        width: 150,
        child: Stack(
          children: [
            CustomPaint(
              size: const Size(150, 100),
              painter: SemiCircleProgressPainter(
                progress: progress,
                context: context,
              ),
            ),
            Positioned.fill(
              child: Align(
                alignment: Alignment.center,
                child: Padding(
                  padding: const EdgeInsets.only(top: 15),
                  child: Text.rich(
                    TextSpan(
                      children: [
                        TextSpan(
                          text: '$remaining',
                          style: TextStyle(
                            fontSize: 20,
                            fontWeight: FontWeight.w600,
                            color: Theme.of(context).colorScheme.primary,
                          ),
                        ),
                        TextSpan(
                          text: '\nKalorien\nübrig',
                          style: const TextStyle(
                            fontSize: 20,
                            fontWeight: FontWeight.w600,
                          ),
                        ),
                      ],
                    ),
                    textAlign: TextAlign.center,
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildBurnedCaloriesCircle(BuildContext context, TrainingData data) {
    final burned = _calculateBurnedCalories(data);
    final total = _calculateTotalCalories(data);
    final progress = total > 0 ? (burned / total).clamp(0.0, 1.0) : 0.0;

    return Center(
      child: SizedBox(
        height: 100,
        width: 150,
        child: Stack(
          children: [
            CustomPaint(
              size: const Size(150  , 100),
              painter: SemiCircleProgressPainter(
                progress: progress,
                context: context,
              ),
            ),
            Positioned.fill(
              child: Align(
                alignment: Alignment.center,
                child: Padding(
                  padding: const EdgeInsets.only(top: 15),
                  child: Text.rich(
                    TextSpan(
                      children: [
                        TextSpan(
                          text: '${burned.toInt()} / ${total.toInt()}',
                          style: TextStyle(
                            fontSize: 20,
                            fontWeight: FontWeight.w500,
                            color: Theme.of(context).colorScheme.primary,
                          ),
                        ),
                        TextSpan(
                          text: '\nKalorien verbrannt',
                          style: const TextStyle(
                            fontSize: 20,
                            fontWeight: FontWeight.w500,
                          ),
                        ),
                      ],
                    ),
                    textAlign: TextAlign.center,
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  double _calculateBurnedCalories(TrainingData data) {
    double burned = 0;
    for (final task in data.currentPlan.tasks) {
      if (task.isCompleted) {
        burned += task.calories;
      }
    }
    return burned;
  }

  double _calculateTotalCalories(TrainingData data) {
    return data.currentPlan.tasks.fold<double>(
      0,
      (sum, task) => sum + task.calories,
    );
  }
}