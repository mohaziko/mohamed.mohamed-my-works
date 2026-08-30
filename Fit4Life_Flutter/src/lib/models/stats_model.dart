import 'package:flutter/material.dart';
import 'package:src/models/section_title_model.dart';
import 'package:src/models/leaderboard_model.dart';
import 'dart:math';

class StatsModelConstants {
  static const double sectionSpacing = 32;
  static const double contentPadding = 20;
}

class StatisticsData {
  final int pointsTotal;
  final int pointsWeek;
  final List<double> pointsHistory; 
  final List<double> caloriesHistory;

  StatisticsData({
    required this.pointsTotal,
    required this.pointsWeek,
    required this.pointsHistory,
    required this.caloriesHistory,
  });
}

class StatsPageModel extends StatelessWidget {
  final StatisticsData data;
  const StatsPageModel({super.key, required this.data});

  @override
  Widget build(BuildContext context) {
    final Color primaryColor = Theme.of(context).colorScheme.primary;
    
    // FIX: Feste Labels für Mo-So (passend zur Datenbank-Logik)
    final List<String> labels = ['Mo', 'Di', 'Mi', 'Do', 'Fr', 'Sa', 'So'];
    
    // Highlight für den aktuellen Wochentag berechnen (Mo=0 ... So=6)
    // Damit der Kreis für "Heute" größer dargestellt wird.
    final int todayIndex = DateTime.now().weekday - 1;

    return SingleChildScrollView(
      child: Padding(
        padding: const EdgeInsets.all(StatsModelConstants.contentPadding),
        child: Column(
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                SectionTitleModel(title: 'Deine Erfolge'),
                OutlinedButton.icon(
                  onPressed: () {
                    showDialog(
                      context: context,
                      barrierDismissible: true, 
                      builder: (BuildContext context) => const LeaderboardDialog(),
                    );
                  },
                  icon: Icon(Icons.emoji_events_outlined, color: primaryColor),
                  label: Text("Bestenliste", style: TextStyle(color: primaryColor)),
                  style: OutlinedButton.styleFrom(
                    shape: const StadiumBorder(), 
                    side: BorderSide(color: primaryColor)
                  ),
                ),
              ],
            ),
            const SizedBox(height: 40),
            const Text('Punkte Gesamt', style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold, color: Colors.grey)),
            const SizedBox(height: 12),
            _buildCenteredScoreBox("${data.pointsTotal} Punkte", primaryColor),
            const SizedBox(height: StatsModelConstants.sectionSpacing),
            const Text('Punkte diese Woche', style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold, color: Colors.grey)),
            const SizedBox(height: 12),
            _buildCenteredScoreBox("${data.pointsWeek}", primaryColor),
            const SizedBox(height: 50),
            const Align(
              alignment: Alignment.centerLeft,
              // FIX: Text geändert
              child: Text('GESAMTE WOCHE', style: TextStyle(fontSize: 14, fontWeight: FontWeight.bold, color: Colors.grey)),
            ),
            const SizedBox(height: 16),
            Row(
              children: [
                Expanded(child: _buildChartBox("Punkte", data.pointsHistory, primaryColor, labels, todayIndex)),
                const SizedBox(width: 16),
                Expanded(child: _buildChartBox("Kalorien", data.caloriesHistory, Colors.orange, labels, todayIndex)),
              ],
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildCenteredScoreBox(String text, Color color) {
    return Container(
      width: 280,
      padding: const EdgeInsets.symmetric(vertical: 20),
      decoration: BoxDecoration(
        color: color.withAlpha(50), 
        borderRadius: BorderRadius.circular(15),
        border: Border.all(color: color.withAlpha(80), width: 1),
      ),
      child: Center(child: Text(text, style: TextStyle(fontSize: 26, fontWeight: FontWeight.bold, color: color))),
    );
  }

  // Update: added todayIndex parameter
  Widget _buildChartBox(String title, List<double> values, Color color, List<String> labels, int todayIndex) {
    double maxValue = values.isEmpty ? 0 : values.reduce(max);
    const double sidePadding = 15.0;

    return Column(
      children: [
        Text(title, style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 13)),
        const SizedBox(height: 10),
        LayoutBuilder(
          builder: (context, constraints) {
            double yAxisSpace = 29;
            double chartWidth = constraints.maxWidth - yAxisSpace;
            double drawableWidth = chartWidth - (sidePadding * 2);
            double stepWidth = drawableWidth / 6;

            return Column(
              children: [
                Row(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    SizedBox(
                      width: 25,
                      child: Text(maxValue.toInt().toString(), style: const TextStyle(fontSize: 10, color: Colors.grey)),
                    ),
                    const SizedBox(width: 4),
                    Expanded(
                      child: Container(
                        height: 100,
                        decoration: BoxDecoration(color: color.withAlpha(50), borderRadius: BorderRadius.circular(12)),
                        child: CustomPaint(
                          // FIX: Übergebe todayIndex statt festem Wert "6"
                          painter: StatsLinePainter(values, color, todayIndex, sidePadding),
                        ),
                      ),
                    ),
                  ],
                ),
                const SizedBox(height: 8),
                Padding(
                  padding: EdgeInsets.only(left: yAxisSpace + sidePadding),
                  child: SizedBox(
                    width: double.infinity,
                    height: 20,
                    child: Stack(
                      clipBehavior: Clip.none,
                      children: List.generate(7, (i) {
                        // Prüfen ob es "Heute" ist für Fettdruck
                        bool isToday = (i == todayIndex);
                        return Positioned(
                          left: (i * stepWidth) - 15,
                          child: SizedBox(
                            width: 30,
                            child: Text(
                              labels[i],
                              textAlign: TextAlign.center,
                              style: TextStyle(
                                fontSize: 10,
                                fontWeight: isToday ? FontWeight.bold : FontWeight.normal,
                                color: isToday ? color : Colors.grey,
                              ),
                            ),
                          ),
                        );
                      }),
                    ),
                  ),
                ),
              ],
            );
          }
        ),
      ],
    );
  }
}

class StatsLinePainter extends CustomPainter {
  final List<double> values;
  final Color color;
  final int highlightIndex;
  final double horizontalPadding;

  StatsLinePainter(this.values, this.color, this.highlightIndex, this.horizontalPadding);

  @override
  void paint(Canvas canvas, Size size) {
    if (values.length < 2) return;
    
    final linePaint = Paint()..color = color..strokeWidth = 3..style = PaintingStyle.stroke..strokeCap = StrokeCap.round;
    final path = Path();
    
    double drawableWidth = size.width - (horizontalPadding * 2);
    double dx = drawableWidth / 6;
    double maxVal = values.reduce(max);
    if (maxVal == 0) maxVal = 1;

    List<Offset> points = [];
    for (int i = 0; i < values.length; i++) {
      double x = horizontalPadding + (i * dx);
      double y = size.height - (values[i] / maxVal * size.height * 0.7) - (size.height * 0.15);
      points.add(Offset(x, y));
      if (i == 0) path.moveTo(x, y); else path.lineTo(x, y);
    }

    canvas.drawPath(path, linePaint);

    for (int i = 0; i < points.length; i++) {
      bool isToday = (i == highlightIndex);
      canvas.drawCircle(points[i], isToday ? 6 : 4, Paint()..color = color);
      canvas.drawCircle(points[i], isToday ? 3 : 2, Paint()..color = Colors.white);
      if (isToday) {
        canvas.drawCircle(points[i], 10, Paint()..color = color.withAlpha(40));
      }
    }
  }
  @override bool shouldRepaint(covariant CustomPainter oldDelegate) => true;
}