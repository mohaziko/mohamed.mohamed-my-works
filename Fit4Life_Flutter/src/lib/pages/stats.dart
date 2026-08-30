import 'package:flutter/material.dart';
import 'package:src/handler/stats_handler.dart';

class StatisticsPage extends StatelessWidget {
  const StatisticsPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.white,
      appBar: AppBar(
        elevation: 0,
        backgroundColor: Theme.of(context).colorScheme.primary,
        leading: IconButton(
          icon: const Icon(Icons.arrow_back, color: Colors.white),
          onPressed: () => Navigator.pop(context),
        ),
        centerTitle: true,
        title: const Text("Statistiken", 
          style: TextStyle(color: Colors.white, fontWeight: FontWeight.bold)),
      ),
      body: const SafeArea(child: StatsHandler()),
    );
  }
}