import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:src/handler/social_handler.dart';

import 'package:src/pages/food.dart';
import 'package:src/pages/home.dart';
import 'package:src/pages/profile.dart';
import 'package:src/pages/stats.dart';
import 'package:src/pages/training.dart';

class Dashboard extends StatefulWidget {
  const Dashboard({super.key});

  @override
  State<Dashboard> createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  int _selectedIndex = 1;

  final PageController _pageController = PageController(initialPage: 1);
  final ValueNotifier<int> _homeRefreshSignal = ValueNotifier<int>(0);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: buildAppBar(context),
      body: PageView(
        controller: _pageController,
        onPageChanged: (index) {
          setState(() {
            _selectedIndex = index;
          });
        },
        children: [
          FoodPage(),
          HomePage(pageController: _pageController, refreshSignal: _homeRefreshSignal),
          TrainingPage(),
        ],
      ),
      bottomNavigationBar: buildBottomNavigationBar(context),
    );
  }

  BottomNavigationBar buildBottomNavigationBar(BuildContext context) {
    return BottomNavigationBar(
      currentIndex: _selectedIndex,
      onTap: (index) {
        _pageController.animateToPage(index, 
          duration: const Duration(milliseconds: 300), 
          curve: Curves.ease
        );
        HapticFeedback.selectionClick();
      },
      items: const [
        BottomNavigationBarItem(label: "Essen", icon: Icon(Icons.local_dining)),
        BottomNavigationBarItem(label: "Home", icon: Icon(Icons.home)),
        BottomNavigationBarItem(label: "Training", icon: Icon(Icons.fitness_center))
      ],
      iconSize: 40,
      backgroundColor: Theme.of(context).colorScheme.primary,
      unselectedItemColor: Theme.of(context).colorScheme.inversePrimary,
      selectedItemColor: Theme.of(context).colorScheme.onPrimary,
      showUnselectedLabels: false,
    );
  }

  AppBar buildAppBar(BuildContext context) {
    return AppBar(
      backgroundColor: Theme.of(context).colorScheme.primary,
      iconTheme: IconThemeData(
        color: Theme.of(context).colorScheme.onPrimary,
        size: 40,
      ),
      leading: IconButton(
        icon: const Icon(Icons.group),
        padding: const EdgeInsets.only(left: 32),
        tooltip: "Soziales",
        onPressed: () {
          Navigator.push(context, MaterialPageRoute(builder: (context) => SocialPageHandler()));
          HapticFeedback.selectionClick(); 
        },
      ),
      actions: [
        IconButton(
          icon: const Icon(Icons.bar_chart),
          padding: const EdgeInsets.only(right: 16),
          tooltip: "Statistiken",
          onPressed: () {
            Navigator.push(context, MaterialPageRoute(builder: (context) => const StatisticsPage()));
            HapticFeedback.selectionClick();
          },
        ),
        IconButton(
          icon: const Icon(Icons.account_circle),
          padding: const EdgeInsets.only(right: 32),
          tooltip: "Profil",
          onPressed: () {
            Navigator.push(
              context, 
              MaterialPageRoute(builder: (context) => const ProfilPage())
            ).then((_) {
              // Trigger Home refresh when returning from Profile
              _homeRefreshSignal.value++;
            });
            HapticFeedback.selectionClick();
          },
        ),
      ],
    );
  }
  }
