import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:src/data/training_data.dart';
import 'package:src/models/food/progress_semi_circle.dart';
import 'package:src/models/section_title_model.dart';
import 'package:src/models/card_container_model.dart';
import 'package:src/dialogs/training_search_dialog.dart';
import 'package:src/models/training/training_checkbox_tile.dart';
import 'package:src/models/info_bar_model.dart';
import 'package:share_plus/share_plus.dart';
import 'package:src/crud/trainingcrud.dart';
import 'package:src/crud/profilcrud.dart'; 

class TrainingDayModelConstants {
  static const double contentPadding = 16.0;
  static const double sectionSpacing = 24.0;
  static const double mediumSpacing = 12.0;
}

class TrainingDayModel extends StatefulWidget {
  const TrainingDayModel({
    super.key,
    required this.date,
    required this.data,
  });

  final TrainingData data;
  final DateTime date;

  @override
  State<TrainingDayModel> createState() => _TrainingDayModelState();
}

class _TrainingDayModelState extends State<TrainingDayModel> {
  final _crud = TrainingCrud();
  final _profilCrud = ProfilCrud(); 

  @override
  void initState() {
    super.initState();
  }

  void _resetCompletionStates(TrainingPlan plan) {
    for (final task in plan.tasks) {
      task.isCompleted = false;
    }
  }

  double _calculateBurnedCalories() {
    double burned = 0;
    for (final task in widget.data.currentPlan.tasks) {
      if (task.isCompleted) {
        burned += task.calories;
      }
    }
    return burned;
  }

  double _calculateTotalCalories() {
    return widget.data.currentPlan.tasks.fold<double>(
      0,
      (sum, task) => sum + task.calories,
    );
  }

  double _getDifficultyMultiplier(int difficulty) {
    switch (difficulty) {
      case 1: return 1.0; 
      case 2: return 1.5; 
      case 3: return 2.0; 
      default: return 1.0;
    }
  }

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      child: Padding(
        padding: const EdgeInsets.all(TrainingDayModelConstants.contentPadding),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            _buildWorkoutSection(context),
            const SizedBox(height: TrainingDayModelConstants.sectionSpacing),
            _buildBurnedCaloriesSection(context)
          ]
        ),
      ),
    );
  }
  
  Widget _buildWorkoutSection(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        SectionTitleModel(title: "Trainingsplan"),
        const SizedBox(height: TrainingDayModelConstants.mediumSpacing),
        CardContainerModel(
          context: context,
          child: Column(
            children: [
              _buildTaskList(plan: widget.data.currentPlan),
              const SizedBox(height: 16),
              Row(
                children: [
                  Expanded(
                    child: ElevatedButton.icon(
                      onPressed: () {
                        HapticFeedback.selectionClick();
                        _showTrainingPlanDialog(context);
                      },
                      icon: const Icon(Icons.edit),
                      label: const Text("Anpassen"),
                      style: ElevatedButton.styleFrom(
                        padding: const EdgeInsets.symmetric(vertical: 12),
                        backgroundColor: Theme.of(context).colorScheme.primary,
                        foregroundColor: Theme.of(context).colorScheme.onPrimary
                      ),
                    ),
                  ),
                  const SizedBox(width: 12),
                  Expanded(
                    child: ElevatedButton.icon(
                      onPressed: () {
                        final plan = widget.data.currentPlan;
                        final tasksList = plan.tasks
                            .map((task) => '• ${task.name}')
                            .join('\n');
                        final shareText = "Trainingsplan: ${plan.name}\n\n$tasksList\n\nGeteilt von Fit4Life!";
                        SharePlus.instance.share(
                          ShareParams(text: shareText),
                        );
                        HapticFeedback.selectionClick();
                      },
                      icon: Icon(Icons.adaptive.share),
                      label: const Text("Teilen"),
                      style: ElevatedButton.styleFrom(
                        padding: const EdgeInsets.symmetric(vertical: 12),
                        backgroundColor: Theme.of(context).colorScheme.primary,
                        foregroundColor: Theme.of(context).colorScheme.onPrimary,
                      ),
                    ),
                  ),
                ],
              ),
            ],
          ),
        ),
      ],
    );
  }

  Widget _buildBurnedCaloriesSection(BuildContext context) {
    final burned = _calculateBurnedCalories();
    final total = _calculateTotalCalories();
    final progress = total > 0 ? (burned / total).clamp(0.0, 1.0) : 0.0;

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        SectionTitleModel(title: "Verbrannte Kalorien"),
        const SizedBox(height: TrainingDayModelConstants.mediumSpacing),
        CardContainerModel(
          context: context,
          child: Stack(
            alignment: Alignment.center,
            children: [
              CustomPaint(
                size: const Size(125, 100),
                painter: SemiCircleProgressPainter(
                  progress: progress,
                  context: context,
                ),
              ),
              Positioned.fill(
                child: Align(
                  alignment: Alignment.center,
                  child: Padding(
                    padding: const EdgeInsets.only(top: 35),
                    child: Text(
                      '${burned.toInt()} / ${total.toInt()}\nKalorien verbrannt',
                      textAlign: TextAlign.center,
                      style: const TextStyle(
                        fontSize: 16,
                        fontWeight: FontWeight.w500,
                      ),
                    ),
                  ),
                ),
              ),
            ],
          ),
        ),
      ],
    );
  }

  Widget _buildTaskList({required TrainingPlan plan}) {
    return Column(
      children: plan.tasks.asMap().entries.map((entry) {
        final index = entry.key;
        final task = entry.value;
        final isLast = index == plan.tasks.length - 1;

        return Column(
          children: [
            TrainingCheckboxTile(
              key: ValueKey(task.name), 
              value: task.isCompleted,
              onChanged: (bool? newValue) async {
                bool isChecked = newValue ?? false;

                setState(() {
                  task.isCompleted = isChecked;
                  HapticFeedback.selectionClick();
                });
                
                // 1. Checkbox-Status speichern
                await _crud.saveDay(widget.date, widget.data);

                // --- 2. PUNKTE & HISTORIE ---
                
                double multiplier = _getDifficultyMultiplier(plan.difficulty);
                int points = (task.calories * multiplier).round();
                
                // Kalorien auf 0.0 setzen, damit Sport nicht als Essen gezählt wird
                double eatenCalories = 0.0; 

                if (isChecked) {
                  // HIER: widget.date übergeben!
                  await _profilCrud.addScoreAndHistory(
                    points: points, 
                    calories: eatenCalories, 
                    date: widget.date 
                  );
                  
                  if (mounted) {
                    String message = "Du hast $points Punkte erhalten!";
                    showInfoBar(context, message);
                  }
                } else {
                  // Beim Abwählen wieder abziehen
                  await _profilCrud.addScoreAndHistory(
                    points: -points, 
                    calories: -eatenCalories, 
                    date: widget.date
                  );
                }
              },
              title: task.name,
            ),
            if (!isLast) const Divider(height: 1),
          ],
        );
      }).toList(),
    );
  }

  void _showTrainingPlanDialog(BuildContext context) {
    showDialog(
      context: context,
      builder: (context) => TrainingSearchDialog(
        trainingPlans: widget.data.availablePlans,
        currentPlan: widget.data.currentPlan,
        onPlanSelected: (selectedPlan) async {
          HapticFeedback.selectionClick();
          showInfoBar(
            context,
            'Trainingsplan gewechselt zu: ${selectedPlan.name}',
          );

          setState(() {
            widget.data.currentPlan = selectedPlan;
            _resetCompletionStates(selectedPlan); 
          });
          await _crud.saveDay(widget.date, widget.data);
        },
      ),
    );
  }
}