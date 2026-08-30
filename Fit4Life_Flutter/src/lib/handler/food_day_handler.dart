import 'package:flutter/material.dart';
import 'package:src/crud/foodcrud.dart';
import 'package:src/data/food_data.dart';
import 'package:src/models/food/food_day_model.dart';



class FoodDayHandler extends StatefulWidget {
  const FoodDayHandler({super.key, required this.selectedDate});
  
  final DateTime selectedDate;

  @override
  State<FoodDayHandler> createState() => _FoodDayHandlerState();
}

class _FoodDayHandlerState extends State<FoodDayHandler> {
  final _crud = FoodCrud();
  NutritionData? _data;
  bool _loading = true;

  @override
  void initState() {
    super.initState();
    _loadData();
  }

  Future<void> _loadData() async {
    final loaded = await _crud.loadDay(widget.selectedDate);
    setState(() {
      _data = loaded;
      _loading = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    if (_loading || _data == null) {
      return const Center(child: CircularProgressIndicator());
    }

    return FoodDayModel(
      date: widget.selectedDate,
      data: _data!,
      availableFoods: availableFoods,
    );
  }
}
