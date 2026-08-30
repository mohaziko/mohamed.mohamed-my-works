import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:hive_ce_flutter/hive_flutter.dart';
import 'package:provider/provider.dart';

import 'package:src/dashboard.dart';
import 'package:src/handler/profile_handler.dart';


Future<void> clearAllHiveData() async {
  await Hive.box("userdata").clear();
  await Hive.box("fooddata").clear();
  await Hive.box("trainingdata").clear();
  await Hive.box("socialdatahandler").clear();
  await Hive.box("statsdatahandler").clear();
  await Hive.box("profildata").clear();
}

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await Hive.initFlutter("localdata");
  await Hive.openBox("userdata");
  await Hive.openBox("fooddata");
  await Hive.openBox("trainingdata");
  await Hive.openBox("socialdatahandler");
  await Hive.openBox("statsdatahandler");
  await Hive.openBox("userdata");
  await Hive.openBox("profildata");

  runApp(
    MultiProvider(
      providers: [
        ChangeNotifierProvider(create: (_) => ProfilHandler()..loadProfil()),
      ],
      child: const MyApp(),
    ),
  );
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    SystemChrome.setPreferredOrientations([
      DeviceOrientation.portraitUp,
      DeviceOrientation.portraitDown,
    ]);

    return MaterialApp(
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.blue),
        useMaterial3: true,
      ),
      home: const Dashboard(),
    );
  }
}