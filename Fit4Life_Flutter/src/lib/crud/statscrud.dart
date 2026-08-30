import 'package:src/crud/crudtemplate.dart';
import 'package:src/crud/profilcrud.dart'; 

class StatsCrud extends Crud {
  StatsCrud() : super(dbName: 'statisticsdata');

  final ProfilCrud _profilCrud = ProfilCrud(); 

  Future<Map<String, dynamic>> getMockedStats() async {
    final profil = await _profilCrud.getProfil();
    
    // Tages-Punkte berechnen (für "pointsWeek" oder ähnliches Widget)
    // Wir nehmen einfach die Summe der Historie als Wochen-Score
    double pointsThisWeek = profil.pointsHistory.reduce((a, b) => a + b);

    return {
      'pointsTotal': profil.score, 
      'pointsWeek': pointsThisWeek.toInt(), // Summe der Woche
      'pointsHistory': profil.pointsHistory, // Echte Daten aus DB
      'caloriesHistory': profil.caloriesHistory, // Echte Daten aus DB
    };
  }
}