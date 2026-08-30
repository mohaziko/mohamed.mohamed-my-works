import 'package:hive_ce_flutter/hive_flutter.dart';

class Crud {
  final String dbName;
  late Future<Box> dbBox;

  Crud({required this.dbName}) {
    dbBox = Hive.openBox(dbName);
  }

  Future<void> saveToDB(String key, dynamic value) async {
    final box = await dbBox;
    await box.put(key, value);
  }
}
