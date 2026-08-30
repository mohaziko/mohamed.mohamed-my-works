class NutritionData {
  final int caloriesGoal;
  final double fatsGoal;
  final double proteinGoal;
  final double waterGoal;
  int caloriesConsumed;
  double fatsConsumed;
  double proteinConsumed;
  double waterConsumed;
  int filledGlasses;
  List<Map<String, dynamic>> foods; 

  NutritionData({
    this.caloriesConsumed = 0,
    this.caloriesGoal = 2000,
    this.fatsConsumed = 0.0,
    this.fatsGoal = 80.0,
    this.proteinConsumed = 0.0,
    this.proteinGoal = 150.0,
    this.waterConsumed = 0.0,
    this.waterGoal = 2.0,
    this.filledGlasses = 0,
    this.foods = const [],
  });
}


final List<Map<String, dynamic>> availableFoods = [
    {'name': 'Apfel', 'calories': 52, 'fats': 0.2, 'protein': 0.3},
    {'name': 'Banane', 'calories': 89, 'fats': 0.3, 'protein': 1.1},
    {'name': 'Pizza', 'calories': 300, 'fats': 12.0, 'protein': 12.0},
    {'name': 'Bier 0,5L', 'calories': 200, 'fats': 0.0, 'protein': 1.6},
    {'name': 'Kuchen', 'calories': 400, 'fats': 18.0, 'protein': 5.0},
  ];