import 'package:flutter/material.dart';

import 'package:src/handler/food_day_handler.dart';
import 'package:src/models/calender_model.dart';

class FoodPage extends StatefulWidget {
  const FoodPage({super.key});

  @override
  State<FoodPage> createState() => _FoodPageState();
}

class _FoodPageState extends State<FoodPage> {
  DateTime selectedDate = DateTime.now();

  @override
Widget build(BuildContext context) {
  return Scaffold(
    body: SafeArea(
      child: Column(
        children: [
          CalenderModel(
            onDateSelected: (date) {
              setState(() {
                selectedDate = date;
              });
            },
          ),
          Expanded(
            child: FoodDayHandler(
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