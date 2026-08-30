import 'package:flutter/foundation.dart'; // Für debugPrint
import 'crudtemplate.dart';
import '../models/profil_model.dart';

class ProfilCrud extends Crud {
  ProfilCrud() : super(dbName: 'profildata');

  final String _profileKey = 'user_profile_data';

  Future<ProfilModel> getProfil() async {
    final box = await dbBox;
    final map = box.get(_profileKey);

    if (map != null) {
      return ProfilModel.fromMap(Map<String, dynamic>.from(map));
    }

    // Default Profil, falls noch keines existiert
    return ProfilModel(
      name: "Vorname Nachname",
      username: "profile1337",
      groesse: "180",
      gewicht: "75",
      alter: "21",
      geschlecht: "M",
      pushEnabled: true,
      imagePath: null,
      score: 0, 
    );
  }

  Future<void> updateProfil(ProfilModel profil) async {
    await saveToDB(_profileKey, profil.toMap());
  }

  Future<void> addScoreAndHistory({
    required int points, 
    required double calories, 
    required DateTime date
  }) async {
    final currentProfil = await getProfil();
    
    final newScore = currentProfil.score + points;

    // Explizite Zuweisung des Wochentags
    int dayIndex = 0;
    switch (date.weekday) {
      case DateTime.monday: dayIndex = 0; break;
      case DateTime.tuesday: dayIndex = 1; break;
      case DateTime.wednesday: dayIndex = 2; break;
      case DateTime.thursday: dayIndex = 3; break;
      case DateTime.friday: dayIndex = 4; break;
      case DateTime.saturday: dayIndex = 5; break;
      case DateTime.sunday: dayIndex = 6; break;
      default: dayIndex = 0;
    }

    debugPrint("Speichere -> Datum: $date | Wochentag: ${date.weekday} | Index: $dayIndex");

    List<double> newPointsHistory = List.from(currentProfil.pointsHistory);
    List<double> newCaloriesHistory = List.from(currentProfil.caloriesHistory);

    if (newPointsHistory.length < 7) newPointsHistory = List.filled(7, 0.0);
    if (newCaloriesHistory.length < 7) newCaloriesHistory = List.filled(7, 0.0);

    newPointsHistory[dayIndex] += points;
    newCaloriesHistory[dayIndex] += calories;

    final updated = currentProfil.copyWith(
      score: newScore,
      pointsHistory: newPointsHistory,
      caloriesHistory: newCaloriesHistory,
    );
    
    await updateProfil(updated);
  }

  // --- NEU: Die fehlende Methode "watchProfil" ---
  // Diese Methode liefert einen Stream zurück, der sich meldet, 
  // sobald sich etwas in der Datenbank ändert.
  Stream<ProfilModel> watchProfil() async* {
    final box = await dbBox;

    // 1. Sofort den aktuellen Stand senden (damit man nicht warten muss)
    yield await getProfil();

    // 2. Auf Änderungen lauschen (Hive .watch)
    yield* box.watch(key: _profileKey).map((event) {
      if (event.value != null) {
        return ProfilModel.fromMap(Map<String, dynamic>.from(event.value));
      }
      // Fallback, falls Daten gelöscht wurden (sollte nicht passieren)
      return ProfilModel(
        name: "Vorname Nachname",
        username: "profile1337",
        groesse: "180",
        gewicht: "75",
        alter: "21",
        geschlecht: "M",
        pushEnabled: true,
        score: 0,
      );
    });
  }
}