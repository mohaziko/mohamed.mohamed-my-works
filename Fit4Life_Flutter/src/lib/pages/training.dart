import 'package:flutter/material.dart';

import 'package:src/handler/training_day_handler.dart';
import 'package:src/models/calender_model.dart';
  
class TrainingPage extends StatefulWidget {
  const TrainingPage({super.key});

  @override
  State<TrainingPage> createState() => _TrainingPageState();
}

class _TrainingPageState extends State<TrainingPage> {
  DateTime selectedDate = DateTime.now();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SafeArea(
        child: Column(
          children: [
            CalenderModel(
              daysInFuture: 7,
              onDateSelected: (date) {
                setState(() {
                  selectedDate = date;
                });
              },
            ),
          Expanded(
            child: TrainingDayHandler(
              key: ValueKey(selectedDate),
              selectedDate: selectedDate,
            ),
          ),
          ],
        ),
      ),
    );
  }
}