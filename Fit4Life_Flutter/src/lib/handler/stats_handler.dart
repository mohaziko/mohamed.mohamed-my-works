import 'package:flutter/material.dart';
import 'package:src/crud/statscrud.dart';
import 'package:src/models/stats_model.dart';

class StatsHandler extends StatefulWidget {
  const StatsHandler({super.key});
  @override
  State<StatsHandler> createState() => _StatsHandlerState();
}

class _StatsHandlerState extends State<StatsHandler> {
  final _crud = StatsCrud();
  bool _loading = true;
  StatisticsData? _data;

  @override
  void initState() {
    super.initState();
    _load();
  }

  void _load() async {
    final raw = await _crud.getMockedStats();
    setState(() {
      _data = StatisticsData(
        pointsTotal: raw['pointsTotal'],
        pointsWeek: raw['pointsWeek'],
        pointsHistory: List<double>.from(raw['pointsHistory']),
        caloriesHistory: List<double>.from(raw['caloriesHistory']),
      );
      _loading = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    if (_loading || _data == null) return const Center(child: CircularProgressIndicator());
    return StatsPageModel(data: _data!);
  }
}