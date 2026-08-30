class Task {
  final String name;
  final double calories;
  bool isCompleted;

  Task({
    required this.name,
    required this.calories,
    this.isCompleted = false,
  });
}

class TrainingPlan {
  final String name;
  final int difficulty;
  final String? description;
  final List<Task> tasks;

  TrainingPlan({
    required this.name,
    required this.difficulty,
    required this.tasks,
    this.description,
  });
}

class TrainingData {
  TrainingPlan currentPlan;
  final List<TrainingPlan> availablePlans;

  TrainingData({
    required this.currentPlan,
    required this.availablePlans,
  });
}

final List<TrainingPlan> availableTrainingPlans = [
  // --- Schwierigkeit 1: Anfänger ---
  TrainingPlan(
    name: 'Cardio Einsteiger',
    description: 'Leichte Cardio-Übungen für Anfänger.',
    difficulty: 1,
    tasks: [
      Task(name: "5 Minuten Aufwärmen", calories: 40),
      Task(name: "Jumping Jacks 3 Minuten", calories: 50),
      Task(name: "Leichtes Joggen 4 Minuten", calories: 60),
      Task(name: "Dehnen 5 Minuten", calories: 30),
    ],
  ),
  TrainingPlan(
    name: 'Ganzkörper Anfänger',
    description: 'Einfache Übungen für den ganzen Körper.',
    difficulty: 1,
    tasks: [
      Task(name: "Kniebeugen 3x10", calories: 45),
      Task(name: "Liegestütze auf Knien 3x8", calories: 35),
      Task(name: "Ausfallschritte 3x10 pro Bein", calories: 50),
      Task(name: "Plank 20 Sekunden x3", calories: 25),
    ],
  ),
  TrainingPlan(
    name: 'Beweglichkeitsroutine',
    description: 'Ein sanftes Programm für mehr Flexibilität.',
    difficulty: 1,
    tasks: [
      Task(name: "Nackendehnung 2 Minuten", calories: 20),
      Task(name: "Schulterkreisen 2 Minuten", calories: 15),
      Task(name: "Rumpfbeugen 3 Minuten", calories: 25),
      Task(name: "Seitliche Dehnung 3 Minuten", calories: 20),
    ],
  ),
  // --- Schwierigkeit 2: Fortgeschrittene ---
  TrainingPlan(
    name: 'Krafttraining Mittelstufe',
    description: 'Kombination aus Kraftübungen mit moderater Intensität.',
    difficulty: 2,
    tasks: [
      Task(name: "Kniebeugen mit Sprung 4x12", calories: 80),
      Task(name: "Liegestütze 4x15", calories: 70),
      Task(name: "Mountain Climbers 3x45 Sekunden", calories: 100),
      Task(name: "Plank 45 Sekunden x4", calories: 60),
    ],
  ),
  TrainingPlan(
    name: 'Cardio Intensiv',
    description: 'Intensives Herz-Kreislauf-Training für mehr Ausdauer.',
    difficulty: 2,
    tasks: [
      Task(name: "Burpees 3x12", calories: 120),
      Task(name: "High Knees 4x45 Sekunden", calories: 90),
      Task(name: "Seitstütz 3x40 Sekunden", calories: 60),
      Task(name: "Schattenboxen 3 Minuten", calories: 80),
    ],
  ),
  TrainingPlan(
    name: 'Core Fokus',
    description: 'Zielt auf die Stärkung der Rumpfmuskulatur.',
    difficulty: 2,
    tasks: [
      Task(name: "Crunches 4x20", calories: 50),
      Task(name: "Beinheben 4x15", calories: 60),
      Task(name: "Plank Schulter Tip 3x30 Sekunden", calories: 70),
      Task(name: "Bicycle Crunches 4x20", calories: 80),
    ],
  ),
  // --- Schwierigkeit 3: Profi ---
  TrainingPlan(
    name: 'HIIT Extrem',
    description: 'Hochintensives Intervalltraining für Profis.',
    difficulty: 3,
    tasks: [
      Task(name: "Burpees mit Sprung 5x15", calories: 150),
      Task(name: "Sprints 60 Sekunden x6", calories: 100),
      Task(name: "Liegestütz-Claps 4x12", calories: 90),
      Task(name: "Plank Jacks 4x45 Sekunden", calories: 80),
    ],
  ),
  TrainingPlan(
    name: 'Kraft & Ausdauer Pro',
    description: 'Ein herausfordernder Mix aus Kraft und Cardio.',
    difficulty: 3,
    tasks: [
      Task(name: "Kettlebell Swings 5x20", calories: 120),
      Task(name: "Pistol Squats 4x10 pro Bein", calories: 110),
      Task(name: "Pull-Ups 5x8", calories: 90),
      Task(name: "Burpee Tuck Jumps 4x12", calories: 130),
    ],
  ),
  TrainingPlan(
    name: 'Athletik Master',
    description: 'Komplexes Athletiktraining für maximale Fitness.',
    difficulty: 3,
    tasks: [
      Task(name: "Box Jumps 5x15", calories: 100),
      Task(name: "Battle Ropes 60 Sekunden x5", calories: 120),
      Task(name: "Handstand Push-Ups 4x8", calories: 90),
      Task(name: "Farmer's Walk 4x60 Sekunden", calories: 80),
    ],
  ),
];
