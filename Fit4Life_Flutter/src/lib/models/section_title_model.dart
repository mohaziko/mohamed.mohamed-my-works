import 'package:flutter/material.dart';

class SectionTitleModelConstants {
  static const double sectionTitleFontSize = 24.0;
}

class SectionTitleModel extends StatelessWidget {
  const SectionTitleModel({super.key, required this.title});

  final String title;

  @override
  Widget build(BuildContext context) {
    return Text(
      title,
      style: const TextStyle(
        fontSize: SectionTitleModelConstants.sectionTitleFontSize,
        fontWeight: FontWeight.bold,
      ),
    );
  }
}