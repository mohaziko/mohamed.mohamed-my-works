import 'package:flutter/material.dart';
import 'package:src/crud/socialcrud.dart';
import 'package:src/crud/profilcrud.dart'; 
import 'package:src/models/contact_model.dart';
import 'package:src/models/profil_model.dart';

class LeaderboardEntry {
  final int rank;
  final String name;
  final int points;
  final bool isMe;

  LeaderboardEntry({
    required this.rank,
    required this.name,
    required this.points,
    this.isMe = false,
  });
}

class LeaderboardDialog extends StatefulWidget {
  const LeaderboardDialog({super.key});

  @override
  State<LeaderboardDialog> createState() => _LeaderboardDialogState();
}

class _LeaderboardDialogState extends State<LeaderboardDialog> {
  bool isLocal = true;
  final SocialCrud _socialCrud = SocialCrud();
  final ProfilCrud _profilCrud = ProfilCrud(); 
  
  List<LeaderboardEntry> _localList = [];
  List<LeaderboardEntry> _globalList = []; 
  
  bool _isLoading = true;

  int _myScore = 0; 
  int _myRankLocal = 0;
  int _myRankGlobal = 0;
  String _myUsername = "Lade..."; 

  // HIER: Deine Liste als Basis für die globalen Daten
  // Wir wandeln sie direkt in LeaderboardEntry um.
  final List<LeaderboardEntry> _globalRawData = [
    LeaderboardEntry(rank: 0, name: "@maxpower", points: 4500),
    LeaderboardEntry(rank: 0, name: "@denniscrossfit", points: 3600),
    LeaderboardEntry(rank: 0, name: "@sarahschmidt", points: 3200),
    LeaderboardEntry(rank: 0, name: "@daniels", points: 3120),
    LeaderboardEntry(rank: 0, name: "@janrunner", points: 2900),
    LeaderboardEntry(rank: 0, name: "@chrisgym", points: 2800),
    LeaderboardEntry(rank: 0, name: "@juliab", points: 2750),
    LeaderboardEntry(rank: 0, name: "@lauraweber", points: 2450),
    LeaderboardEntry(rank: 0, name: "@elenak", points: 2300),
    LeaderboardEntry(rank: 0, name: "@lisarun", points: 2100),
    LeaderboardEntry(rank: 0, name: "@ninaactive", points: 2050),
    LeaderboardEntry(rank: 0, name: "@mehmetyilmaz", points: 1980),
    LeaderboardEntry(rank: 0, name: "@timbergmann", points: 1890),
    LeaderboardEntry(rank: 0, name: "@vanessap", points: 1750),
    LeaderboardEntry(rank: 0, name: "@annayoga", points: 1650),
    LeaderboardEntry(rank: 0, name: "@tommueller", points: 1450),
    LeaderboardEntry(rank: 0, name: "@leapilates", points: 1350),
    LeaderboardEntry(rank: 0, name: "@sophiefit", points: 1200),
    LeaderboardEntry(rank: 0, name: "@fabiansport", points: 1100),
    LeaderboardEntry(rank: 0, name: "@kevink", points: 950),
  ];

  @override
  void initState() {
    super.initState();
    _loadData();
  }

  Future<void> _loadData() async {
    // 1. Echten User laden
    final profil = await _profilCrud.getProfil();
    final String currentUsername = profil.username;
    final int currentScore = profil.score;

    // --- LOKALE LISTE (FREUNDE) ---
    List<ContactData> contacts = await _socialCrud.getContacts();
    var friends = contacts.where((c) => c.type == ChatType.single).toList();

    List<LeaderboardEntry> tempLocal = [];
    for (var friend in friends) {
      tempLocal.add(LeaderboardEntry(
        rank: 0,
        name: friend.username,
        points: friend.score,
        isMe: false,
      ));
    }
    // Dich hinzufügen (Lokal)
    tempLocal.add(LeaderboardEntry(
      rank: 0, 
      name: "Du (@$currentUsername)", 
      points: currentScore, 
      isMe: true
    ));

    // Sortieren & Ränge berechnen (Lokal)
    tempLocal.sort((a, b) => b.points.compareTo(a.points));
    List<LeaderboardEntry> finalLocal = _assignRanks(tempLocal);
    
    // Deinen lokalen Rang finden
    int myRankLocal = finalLocal.indexWhere((e) => e.isMe) + 1; // Sicherer Index + 1


    // --- GLOBALE LISTE ---
    // Wir nehmen deine bereitgestellte Liste als Basis
    List<LeaderboardEntry> tempGlobal = List.from(_globalRawData);
    
    // Dich hinzufügen (Global)
    tempGlobal.add(LeaderboardEntry(
      rank: 0, 
      name: "Du (@$currentUsername)", 
      points: currentScore, 
      isMe: true
    ));

    // Sortieren & Ränge berechnen (Global)
    // Das stellt sicher, dass du zwischen @maxpower (4500) und @kevink (950) richtig einsortiert wirst
    tempGlobal.sort((a, b) => b.points.compareTo(a.points));
    List<LeaderboardEntry> finalGlobal = _assignRanks(tempGlobal);

    // Deinen globalen Rang finden
    int myRankGlobal = finalGlobal.indexWhere((e) => e.isMe) + 1;

    if (mounted) {
      setState(() {
        _localList = finalLocal;
        _globalList = finalGlobal; 
        
        _myRankLocal = myRankLocal;
        _myRankGlobal = myRankGlobal;
        
        _myUsername = currentUsername;
        _myScore = currentScore;
        _isLoading = false;
      });
    }
  }

  // Hilfsmethode um Ränge sauber durchzunummerieren (1, 2, 3...)
  List<LeaderboardEntry> _assignRanks(List<LeaderboardEntry> list) {
    List<LeaderboardEntry> rankedList = [];
    for (int i = 0; i < list.length; i++) {
      rankedList.add(LeaderboardEntry(
        rank: i + 1, // Rang ist Index + 1
        name: list[i].name,
        points: list[i].points,
        isMe: list[i].isMe,
      ));
    }
    return rankedList;
  }

  @override
  Widget build(BuildContext context) {
    final Color primaryColor = Theme.of(context).colorScheme.primary;
    // Dynamisch die richtige Liste wählen
    final currentList = isLocal ? _localList : _globalList;
    // Dynamisch den richtigen Rang für den Footer wählen
    final currentRank = isLocal ? _myRankLocal : _myRankGlobal;

    return Dialog(
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(15)),
      insetPadding: const EdgeInsets.symmetric(horizontal: 20, vertical: 40),
      child: Container(
        padding: const EdgeInsets.all(16),
        decoration: BoxDecoration(
          color: Colors.white,
          borderRadius: BorderRadius.circular(15),
          border: Border.all(color: primaryColor.withAlpha(50)),
        ),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                const Text("Bestenliste", style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold)),
                IconButton(
                  onPressed: () => Navigator.pop(context),
                  icon: const Icon(Icons.close, color: Colors.grey),
                ),
              ],
            ),
            const SizedBox(height: 10),

            Container(
              decoration: BoxDecoration(
                border: Border.all(color: Colors.grey.shade300),
                borderRadius: BorderRadius.circular(8),
              ),
              child: Row(
                children: [
                  Expanded(child: _buildTab("Freunde", isLocal, () => setState(() => isLocal = true), context)),
                  Container(width: 1, height: 40, color: Colors.grey.shade300),
                  Expanded(child: _buildTab("Global", !isLocal, () => setState(() => isLocal = false), context)),
                ],
              ),
            ),
            const SizedBox(height: 10),

            _isLoading
                ? const Padding(padding: EdgeInsets.all(20), child: CircularProgressIndicator())
                : Flexible(
                    child: ListView.builder(
                      shrinkWrap: true,
                      itemCount: currentList.length,
                      itemBuilder: (context, index) {
                        final entry = currentList[index];
                        // Highlight nur wenn es "Du" bist
                        final bool highlight = entry.isMe;

                        return Container(
                          decoration: highlight
                              ? BoxDecoration(color: primaryColor.withAlpha(20), borderRadius: BorderRadius.circular(8))
                              : null,
                          child: ListTile(
                            contentPadding: const EdgeInsets.symmetric(horizontal: 8),
                            leading: Container(
                              width: 30,
                              alignment: Alignment.center,
                              child: Text("${entry.rank}.",
                                  style: TextStyle(
                                      fontWeight: FontWeight.bold,
                                      color: entry.rank <= 3 ? Colors.orange : Colors.black)),
                            ),
                            title: Text(entry.name,
                                style: TextStyle(
                                    fontWeight: highlight ? FontWeight.bold : FontWeight.normal,
                                    color: highlight ? primaryColor : Colors.black)),
                            trailing: Text("${entry.points} Pkt.",
                                style: TextStyle(
                                    color: highlight ? primaryColor : Colors.grey,
                                    fontWeight: highlight ? FontWeight.bold : FontWeight.normal,
                                    fontSize: 13)),
                          ),
                        );
                      },
                    ),
                  ),

            const Divider(thickness: 1),

            // Footer: Zeigt dynamisch deinen Rang (Lokal oder Global)
            Padding(
              padding: const EdgeInsets.only(top: 8.0),
              child: Row(
                children: [
                  SizedBox(
                      width: 30,
                      child: Center(
                          child: Text("$currentRank.", 
                              style: const TextStyle(fontWeight: FontWeight.bold)))),
                  Text("Du (@$_myUsername)", 
                      style: const TextStyle(fontWeight: FontWeight.bold)),
                  const Spacer(),
                  Text("$_myScore Pkt.",
                      style: TextStyle(color: primaryColor, fontWeight: FontWeight.bold)),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildTab(String title, bool active, VoidCallback onTap, BuildContext context) {
    return GestureDetector(
      onTap: onTap,
      child: Container(
        height: 40,
        color: active ? Theme.of(context).colorScheme.primary.withAlpha(30) : Colors.transparent,
        alignment: Alignment.center,
        child: Text(title,
            style: TextStyle(
                fontWeight: FontWeight.bold,
                color: active ? Theme.of(context).colorScheme.primary : Colors.grey)),
      ),
    );
  }
}