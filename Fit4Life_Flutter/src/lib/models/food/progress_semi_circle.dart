import 'package:flutter/material.dart';
import 'dart:math';

class SemiCircleProgressPainter extends CustomPainter {
  final double progress;
  final BuildContext context;

  SemiCircleProgressPainter({
    required this.progress,
    required this.context,
  });

  @override
  void paint(Canvas canvas, Size size) {
    final center = Offset(size.width / 2, size.height);
    final radius = size.width - 30;

    // Hintergrund Halbkreis
    final backgroundPaint = Paint()
      ..color = Theme.of(context).colorScheme.primary.withAlpha(50)
      ..style = PaintingStyle.stroke
      ..strokeWidth = 15
      ..strokeCap = StrokeCap.round;

    canvas.drawArc(
      Rect.fromCircle(center: center, radius: radius),
      pi,
      pi,
      false,
      backgroundPaint,
    );

    // Fortschritt Halbkreis
    final progressPaint = Paint()
      ..color = Theme.of(context).colorScheme.primary
      ..style = PaintingStyle.stroke
      ..strokeWidth = 15
      ..strokeCap = StrokeCap.round;

    canvas.drawArc(
      Rect.fromCircle(center: center, radius: radius),
      pi,
      pi * progress,
      false,
      progressPaint,
    );

    // Punkt am Ende des Fortschritts
    final angle = pi + (pi * progress);
    final pointX = center.dx + radius * cos(angle);
    final pointY = center.dy + radius * sin(angle);
    
    canvas.drawCircle(
      Offset(pointX, pointY),
      10,
      Paint()..color = Theme.of(context).colorScheme.primary,
    );
  }

  @override
  bool shouldRepaint(SemiCircleProgressPainter oldDelegate) {
    return oldDelegate.progress != progress;
  }
}