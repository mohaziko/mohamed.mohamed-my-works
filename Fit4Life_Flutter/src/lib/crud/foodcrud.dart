import 'package:src/crud/crudtemplate.dart';
import 'package:hive_ce_flutter/hive_flutter.dart';
import 'package:src/data/food_data.dart';

class FoodCrud extends Crud {
  FoodCrud() : super(dbName: 'fooddata');

  String _keyForDate(DateTime date) =>
      '${date.year}-${date.month.toString().padLeft(2, '0')}-${date.day.toString().padLeft(2, '0')}';

  // ---------- WATER ----------

  Future<void> updateWater(int glasses, DateTime date) async {
    final key = _keyForDate(date);
    final Box box = await dbBox;
    final existing = (box.get(key) as Map?) ?? {};

    final updated = {
      ...existing,
      'waterGlasses': glasses,
      'waterConsumed': glasses * 0.25,
    };

    await saveToDB(key, updated);
  }

  // ---------- FOOD LIST & METRICS ----------

  Future<void> saveFoodState(
    DateTime date, {
    required int caloriesConsumed,
    required double fatsConsumed,
    required double proteinConsumed,
    required List foods,  // <- flexibel!
    }) async {
    final key = _keyForDate(date);
    final Box box = await dbBox;
    final existing = (box.get(key) as Map?) ?? {};

    final updated = {
      ...existing,
      'caloriesConsumed': caloriesConsumed,
      'fatsConsumed': fatsConsumed,
      'proteinConsumed': proteinConsumed,
      'foods': foods,
    };

    await saveToDB(key, updated);
  }

  // ---------- LOAD DAY ----------

  Future<NutritionData> loadDay(DateTime date) async {
    final key = _keyForDate(date);
    final box = await dbBox;
    final map = (box.get(key) as Map?) ?? {};

    final foodsRaw = ((map['foods'] as List?)?.cast<Map>() ?? <Map<String, dynamic>>[])
    .map((item) => {
          'name': item['name']?.toString() ?? '',
          'calories': (item['calories'] as num?)?.toInt() ?? 0,
          'fats': (item['fats'] as num?)?.toDouble() ?? 0.0,
          'protein': (item['protein'] as num?)?.toDouble() ?? 0.0,
        })
    .toList();


    return NutritionData(
      caloriesConsumed: map['caloriesConsumed'] != null ? map['caloriesConsumed'] as int : NutritionData().caloriesConsumed,
      caloriesGoal: map['caloriesGoal'] != null ? map['caloriesGoal'] as int : NutritionData().caloriesGoal,
      fatsConsumed: map['fatsConsumed'] != null ? (map['fatsConsumed'] as num).toDouble() : NutritionData().fatsConsumed,
      fatsGoal: map['fatsGoal'] != null ? (map['fatsGoal'] as num).toDouble() : NutritionData().fatsGoal,
      proteinConsumed: map['proteinConsumed'] != null ? (map['proteinConsumed'] as num).toDouble() : NutritionData().proteinConsumed,
      proteinGoal: map['proteinGoal'] != null ? (map['proteinGoal'] as num).toDouble() : NutritionData().proteinGoal,
      waterConsumed: map['waterConsumed'] != null ? (map['waterConsumed'] as num).toDouble() : NutritionData().waterConsumed,
      waterGoal: map['waterGoal'] != null ? (map['waterGoal'] as num).toDouble() : NutritionData().waterGoal,
      filledGlasses: map['waterGlasses'] != null ? map['waterGlasses'] as int : NutritionData().filledGlasses,
      foods: foodsRaw,
    );
  }
}
