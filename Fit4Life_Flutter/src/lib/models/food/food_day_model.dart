import 'dart:math';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:src/crud/foodcrud.dart';
import 'package:src/crud/profilcrud.dart'; // NEU: Importieren
import 'package:src/data/food_data.dart';
import 'package:src/models/card_container_model.dart';
import 'package:src/models/section_title_model.dart';
import 'package:src/models/food/progress_semi_circle.dart';
import 'package:src/dialogs/food_search_dialog.dart';
import 'package:src/models/info_bar_model.dart';


class FoodDayModelConstants {
  static const double sectionSpacing = 24;
  static const double contentPadding = 16;
  static const double labelFontSize = 18;
  static const double smallSpacing = 8;
  static const double mediumSpacing = 12;
  static const double verticalDividerWidth = 1;
  static const double verticalDividerHeight = 180;
}

class FoodDayModel extends StatefulWidget {
  const FoodDayModel({
    super.key,
    required this.data,
    required this.date,
    required this.availableFoods,
  });

  final NutritionData data;
  final DateTime date;
  final List<Map<String, dynamic>> availableFoods;

  @override
  State<FoodDayModel> createState() => _FoodDayModelState();
}

class _FoodDayModelState extends State<FoodDayModel> {
  late int caloriesConsumed = widget.data.caloriesConsumed;
  late int caloriesGoal = widget.data.caloriesGoal;
  late double fatsConsumed = widget.data.fatsConsumed;
  late double fatsGoal = widget.data.fatsGoal;
  late double proteinConsumed = widget.data.proteinConsumed;
  late double proteinGoal = widget.data.proteinGoal;
  late double waterConsumed = widget.data.waterConsumed;
  late double waterGoal = widget.data.waterGoal;
  late int filledGlasses = widget.data.filledGlasses;

  late List<Map<String, dynamic>> foods = List<Map<String, dynamic>>.from(widget.data.foods); 

  late final FoodCrud _foodCrud;
  late final ProfilCrud _profilCrud; // NEU: ProfilCrud

  @override
  void initState() {
    super.initState();
    _foodCrud = FoodCrud();
    _profilCrud = ProfilCrud(); // NEU: Initialisieren
  }


  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.all(FoodDayModelConstants.contentPadding),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              _buildFoodSection(context),
              const SizedBox(height: FoodDayModelConstants.sectionSpacing),
              _buildWaterSection(context),
            ],
          ),
        ),
    );
  }

  Widget _buildNutrientBar(String label, double consumed, double goal, Color color) {
    double progress = (consumed / goal).clamp(0.0, 1.0);
    
    return Column(
      crossAxisAlignment: CrossAxisAlignment.center,
      mainAxisSize: MainAxisSize.min,
      children: [
        LayoutBuilder(
          builder: (context, constraints) {
            return Container(
              height: 20,
              width: double.infinity,
              decoration: BoxDecoration(
                color: Theme.of(context).colorScheme.primary.withAlpha(50),
                borderRadius: BorderRadius.circular(10),
              ),
              child: Stack(
                children: [
                  if (progress > 0)
                    Container(
                      width: constraints.maxWidth * progress,
                      decoration: BoxDecoration(
                        color: color,
                        borderRadius: BorderRadius.circular(10),
                      ),
                    ),
                ],
              ),
            );
          },
        ),
        const SizedBox(height: 4),
        Text(
          '${consumed.toInt()}/${goal.toInt()} $label',
          style: const TextStyle(fontSize: 14, fontWeight: FontWeight.w500)
        ),
      ],
    );
  }

  // Food Section
Widget _buildFoodSection(BuildContext context) {
  int caloriesRemaining = caloriesGoal - caloriesConsumed;
  double caloriesProgress = caloriesConsumed / caloriesGoal;

  return Column(
    crossAxisAlignment: CrossAxisAlignment.start,
    children: [
      SectionTitleModel(title: 'Essen'),
      const SizedBox(height: FoodDayModelConstants.mediumSpacing),
      
      CardContainerModel(
        context: context,
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Expanded(
                  child: Column(
                    children: [
                      _buildCalorieCircle(context, caloriesProgress, caloriesRemaining),
                      const SizedBox(height: FoodDayModelConstants.sectionSpacing),
                      Row(
                        children: [
                          Expanded(
                            child: _buildNutrientBar(
                              'Fette',
                              fatsConsumed,
                              fatsGoal,
                              Theme.of(context).colorScheme.primary,
                            ),
                          ),
                          const SizedBox(width: FoodDayModelConstants.mediumSpacing),
                          Expanded(
                            child: _buildNutrientBar(
                              'Eiweiß',
                              proteinConsumed,
                              proteinGoal,
                              Theme.of(context).colorScheme.primary,
                            ),
                          ),
                        ],
                      ),
                    ],
                  ),
                ),
                _buildVerticalDivider(context),
                _buildAddButton(context),
              ],
            ),
            
            const SizedBox(height: 16),
            if (foods.isNotEmpty) ...[
              const Text(
                'Heute gegessen:',
                style: TextStyle(
                  fontSize: 16,
                  fontWeight: FontWeight.w600,
                ),
              ),
              const SizedBox(height: 8),
              ...foods.asMap().entries.map((entry) {
                final index = entry.key;
                final item = entry.value;
                return Container(
                  margin: const EdgeInsets.only(bottom: 8),
                  padding: const EdgeInsets.all(12),
                  decoration: BoxDecoration(
                    color: Colors.grey[100],
                    borderRadius: BorderRadius.circular(8),
                  ),
                  child: Row(
                    children: [
                      Expanded(
                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            Text(
                              item['name'] ?? 'Unbekannt',
                              style: const TextStyle(fontWeight: FontWeight.w600),
                            ),
                            Text(
                              '${item['calories'] ?? 0} kcal | '
                              '${(item['fats'] ?? 0).toStringAsFixed(1)}g F | '
                              '${(item['protein'] ?? 0).toStringAsFixed(1)}g P',
                              style: TextStyle(
                                fontSize: 12,
                                color: Colors.grey[600],
                              ),
                            ),
                          ],
                        ),
                      ),
                      IconButton(
                        icon: const Icon(Icons.delete_outline, color: Colors.red),
                        onPressed: () async {
                          await _removeFoodAt(index);
                        },
                      ),
                    ],
                  ),
                );
              }),
            ] else ...[
              Container(
                padding: const EdgeInsets.all(16),
                decoration: BoxDecoration(
                  color: Colors.grey[100],
                  borderRadius: BorderRadius.circular(8),
                  border: Border.all(color: Colors.grey[300]!),
                ),
                child: const Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Icon(Icons.restaurant_menu_outlined, color: Colors.grey),
                    SizedBox(width: 8),
                    Text(
                      'Noch keine Lebensmittel hinzugefügt',
                      style: TextStyle(color: Colors.grey),
                    ),
                  ],
                ),
              ),
            ],
          ],
        ),
      ),
    ],
  );
}


  // Water Section
  Widget _buildWaterSection(BuildContext context) {
    int waterGlassesGoal = (waterGoal / 0.25).round();

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        SectionTitleModel(title: 'Trinken'),
        const SizedBox(height: FoodDayModelConstants.mediumSpacing),
        CardContainerModel(
          context: context,
          child: Column(
            children: [
              Text(
                '${waterConsumed.toStringAsFixed(2)}L / ${waterGoal.toStringAsFixed(1)}L',
                style: const TextStyle(
                  fontSize: FoodDayModelConstants.labelFontSize,
                  fontWeight: FontWeight.w500,
                ),
              ),
              const SizedBox(height: FoodDayModelConstants.mediumSpacing),
              Wrap(
                spacing: FoodDayModelConstants.mediumSpacing,
                runSpacing: FoodDayModelConstants.mediumSpacing,
                alignment: WrapAlignment.start,
                children: List.generate(
                  waterGlassesGoal,
                  (index) => _buildWaterGlass(
                    index,
                    index < filledGlasses,
                    index == filledGlasses,
                    waterGlassesGoal,
                  ),
                ),
              ),
            ],
          ),
        ),
      ],
    );
  }

  // Calorie Circle
  Widget _buildCalorieCircle(BuildContext context, double progress, int remaining) {
    return SizedBox(
      height: 100,
      width: 120,
      child: Stack(
        children: [
          CustomPaint(
            size: const Size(120, 100),
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
                  '$remaining\nKalorien übrig',
                  textAlign: TextAlign.center,
                  style: const TextStyle(
                    fontSize: 16,
                    fontWeight: FontWeight.w600,
                  ),
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }

  // Vertical Divider
  Widget _buildVerticalDivider(BuildContext context) {
    return Container(
      width: FoodDayModelConstants.verticalDividerWidth,
      height: FoodDayModelConstants.verticalDividerHeight,
      color: Theme.of(context).colorScheme.primary,
      margin: const EdgeInsets.only(left: FoodDayModelConstants.sectionSpacing, right: FoodDayModelConstants.smallSpacing),
    );
  }

  Widget _buildAddButton(BuildContext context) {
    return IconButton(
      onPressed: () async {
        HapticFeedback.selectionClick();
        await _showFoodDialog(context);
      },
      icon: Icon(
        CupertinoIcons.add_circled,
        size: 40,
        color: Theme.of(context).colorScheme.primary,
      ),
    );
  }

  Future<void> _showFoodDialog(BuildContext context) async {
    await showDialog(
      context: context,
      builder: (context) => FoodSearchDialog(
        foods: widget.availableFoods,
        onFoodSelected: (name, calories, fats, protein) async {
          setState(() {
            foods.add({
              'name': name,
              'calories': calories,
              'fats': fats,
              'protein': protein,
            });
            caloriesConsumed += calories;
            fatsConsumed += fats;
            proteinConsumed += protein;
          });

          await _foodCrud.saveFoodState(
            widget.date,
            caloriesConsumed: caloriesConsumed,
            fatsConsumed: fatsConsumed,
            proteinConsumed: proteinConsumed,
            foods: foods,
          );

          // --- NEU: Statistik updaten (Gelbe Kurve hoch) ---
          await _profilCrud.addScoreAndHistory(
            points: 0, // Essen gibt keine Punkte
            calories: calories.toDouble(), // Aber Kalorien
            date: widget.date // Datum beachten!
          );

          showInfoBar(context, 'Hinzugefügt: $name');
        },
      ),
    );
  }


  Widget _buildWaterGlass(int index, bool filled, bool isNext, int waterGlassesGoal) {
    return GestureDetector(
      onTap: () async {
        setState(() {
          if (filled && index == filledGlasses - 1) {
            filledGlasses = (filledGlasses - 1).clamp(0, waterGlassesGoal);
            waterConsumed = max(0, waterConsumed - 0.25);
            HapticFeedback.selectionClick();
          }
          else if (isNext && filledGlasses < waterGlassesGoal) {
            filledGlasses++;
            waterConsumed = min(waterGoal, waterConsumed + 0.25);
            HapticFeedback.selectionClick();
          }
        });

        await _foodCrud.updateWater(filledGlasses, widget.date);

      },
      child: Container(
        width: 40,
        height: 50,
        decoration: BoxDecoration(
          border: Border.all(
            color: Theme.of(context).colorScheme.primary,
            width: 2,
          ),
          borderRadius: const BorderRadius.only(
            bottomLeft: Radius.circular(26),
            bottomRight: Radius.circular(26),
          ),
          color: filled ? Theme.of(context).colorScheme.primary.withAlpha(50) : Colors.transparent,
        ),
        child: isNext
            ? Icon(
                Icons.add,
                color: Theme.of(context).colorScheme.primary,
                size: 25,
              )
            : null,
      ),
    );
  }

Future<void> _removeFoodAt(int index) async {
  final item = foods[index];
  final int c = item['calories'] ?? 0;
  final double f = (item['fats'] ?? 0.0).toDouble();
  final double p = (item['protein'] ?? 0.0).toDouble();

  setState(() {
    foods.removeAt(index);
    caloriesConsumed = (caloriesConsumed - c).clamp(0, caloriesGoal);
    fatsConsumed = (fatsConsumed - f).clamp(0.0, fatsGoal);
    proteinConsumed = (proteinConsumed - p).clamp(0.0, proteinGoal);
  });

  await _foodCrud.saveFoodState(
    widget.date,
    caloriesConsumed: caloriesConsumed,
    fatsConsumed: fatsConsumed,
    proteinConsumed: proteinConsumed,
    foods: foods,
  );

  // --- NEU: Statistik updaten (Gelbe Kurve runter) ---
  await _profilCrud.addScoreAndHistory(
    points: 0, 
    calories: -c.toDouble(), // Negative Kalorien = abziehen
    date: widget.date 
  );

  showInfoBar(context, 'Entfernt: ${item['name'] ?? 'Lebensmittel'}');
}
}