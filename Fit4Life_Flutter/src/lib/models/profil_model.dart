class ProfilModel {
  String name;
  String username;
  String groesse;
  String gewicht;
  String alter;
  bool pushEnabled;
  String? imagePath;
  String geschlecht;
  int score;
  
  // Historie für Mo-So (7 Tage)
  List<double> pointsHistory; 
  List<double> caloriesHistory;

  ProfilModel({
    required this.name,
    required this.groesse,
    required this.username,
    required this.gewicht,
    required this.geschlecht,
    required this.alter,
    required this.pushEnabled,
    this.imagePath,
    this.score = 0,
    // Standardmäßig leere Listen für 7 Tage
    this.pointsHistory = const [0, 0, 0, 0, 0, 0, 0],
    this.caloriesHistory = const [0, 0, 0, 0, 0, 0, 0],
  });

  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'username': username,
      'groesse': groesse,
      'gewicht': gewicht,
      'alter': alter,
      'pushEnabled': pushEnabled,
      'imagePath': imagePath,
      'geschlecht': geschlecht,
      'score': score,
      'pointsHistory': pointsHistory,
      'caloriesHistory': caloriesHistory,
    };
  }

  factory ProfilModel.fromMap(Map<String, dynamic> map) {
    return ProfilModel(
      name: map['name'] ?? "Unbekannt",
      username: map['username'] ?? "username",
      groesse: map['groesse'] ?? "0",
      gewicht: map['gewicht'] ?? "0",
      alter: map['alter'] ?? "0",
      pushEnabled: map['pushEnabled'] ?? true,
      imagePath: map['imagePath'],
      geschlecht: map['geschlecht'] ?? "Unbekannt",
      score: map['score'] ?? 0,
      // Listen sicher laden und casten
      pointsHistory: (map['pointsHistory'] as List<dynamic>?)?.map((e) => (e as num).toDouble()).toList() ?? [0, 0, 0, 0, 0, 0, 0],
      caloriesHistory: (map['caloriesHistory'] as List<dynamic>?)?.map((e) => (e as num).toDouble()).toList() ?? [0, 0, 0, 0, 0, 0, 0],
    );
  }

  ProfilModel copyWith({
    String? name,
    String? username,
    String? groesse,
    String? gewicht,
    String? alter,
    bool? pushEnabled,
    String? imagePath,
    String? geschlecht,
    int? score,
    List<double>? pointsHistory,
    List<double>? caloriesHistory,
  }) {
    return ProfilModel(
      name: name ?? this.name,
      username: username ?? this.username,
      groesse: groesse ?? this.groesse,
      gewicht: gewicht ?? this.gewicht,
      alter: alter ?? this.alter,
      pushEnabled: pushEnabled ?? this.pushEnabled,
      imagePath: imagePath ?? this.imagePath,
      geschlecht: geschlecht ?? this.geschlecht,
      score: score ?? this.score,
      pointsHistory: pointsHistory ?? this.pointsHistory,
      caloriesHistory: caloriesHistory ?? this.caloriesHistory,
    );
  }
}