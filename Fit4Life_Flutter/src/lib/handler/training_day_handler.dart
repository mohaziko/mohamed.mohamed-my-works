import 'package:flutter/material.dart';
import 'package:src/models/training/training_day_model.dart';
import 'package:src/data/training_data.dart';
import 'package:src/crud/trainingcrud.dart';

class TrainingDayHandler extends StatefulWidget {
  const TrainingDayHandler({super.key, required this.selectedDate});

  final DateTime selectedDate;

  @override
  State<TrainingDayHandler> createState() => _TrainingDayHandlerState();
}

class _TrainingDayHandlerState extends State<TrainingDayHandler> {
  final _crud = TrainingCrud();

  TrainingData? _data;
  bool _loading = true;

  @override
  void initState() {
    super.initState();
    _loadForDate(widget.selectedDate);
  }

  Future<void> _loadForDate(DateTime date) async {
    final data = await _crud.loadDay(date, availableTrainingPlans);
    setState(() {
      _data = data;
      _loading = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    if (_loading || _data == null) {
      return const Center(child: CircularProgressIndicator());
    }
    return TrainingDayModel(date: widget.selectedDate, data: _data!);
  }
}
