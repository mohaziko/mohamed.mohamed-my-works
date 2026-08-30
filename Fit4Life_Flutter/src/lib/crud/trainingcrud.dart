import 'package:src/crud/crudtemplate.dart';
import 'package:src/data/training_data.dart';

class TrainingCrud extends Crud {
  TrainingCrud() : super(dbName: 'trainingdata');

  String _keyForDate(DateTime date) =>
      '${date.year}-${date.month.toString().padLeft(2, '0')}-${date.day.toString().padLeft(2, '0')}';

  Future<void> saveDay(DateTime date, TrainingData data) async {
    
    final box = await dbBox;
    final map = {
      'currentPlanName': data.currentPlan.name,
      'tasks': data.currentPlan.tasks.map((t) => {
            'name': t.name,
            'calories': t.calories,
            'isCompleted': t.isCompleted,
          }).toList(),
    };

    await saveToDB(_keyForDate(date), map);
  }

  Future<TrainingData> loadDay(
    DateTime date,
    List<TrainingPlan> availablePlans,
  ) async {
    final key = _keyForDate(date);

    final box = await dbBox;
    final raw = box.get(key);

    if (raw is! Map) {
      final defaultPlan = availablePlans.first;
      for (final t in defaultPlan.tasks) {
        t.isCompleted = false;
      }
      return TrainingData(currentPlan: defaultPlan, availablePlans: availablePlans);
    }

    final map = raw;
    final planName = map['currentPlanName'] as String? ?? availablePlans.first.name;
    final plan = availablePlans.firstWhere((p) => p.name == planName, orElse: () => availablePlans.first);

    final savedTasks = (map['tasks'] as List?)?.cast<Map>() ?? [];
    for (final t in plan.tasks) {
      final match = savedTasks.firstWhere((m) => m['name'] == t.name, orElse: () => {});
      t.isCompleted = (match['isCompleted'] as bool?) ?? false;
    }

    return TrainingData(currentPlan: plan, availablePlans: availablePlans);
  }
}
