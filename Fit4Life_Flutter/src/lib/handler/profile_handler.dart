import 'package:flutter/material.dart';
import '../models/profil_model.dart';
import '../crud/profilcrud.dart';

class ProfilHandler extends ChangeNotifier {
  final ProfilCrud _repository = ProfilCrud();
  
  ProfilModel? _profil;
  bool _isLoading = false;

  ProfilModel? get profil => _profil;
  bool get isLoading => _isLoading;

  Future<void> loadProfil() async {
    _isLoading = true;
    notifyListeners();

    try {
      _profil = await _repository.getProfil();
    } catch (e) {
      debugPrint("Error loading profile: $e");
    } finally {
      _isLoading = false;
      notifyListeners();
    }
  }

  Future<void> updateProfil(ProfilModel updatedProfil) async {
    _profil = updatedProfil;
    notifyListeners();

    try {
      await _repository.updateProfil(updatedProfil);
    } catch (e) {
      debugPrint("Error updating profile: $e");
    }
  }

  Future<void> updatePushEnabled(bool enabled) async {
    if (_profil == null) return;
    updateProfil(_profil!.copyWith(pushEnabled: enabled));
  }

  Future<void> updateName(String name) async {
    if (_profil == null) return;
    updateProfil(_profil!.copyWith(name: name));
  }
Future<void> updateUsername(String username) async {
  if (_profil == null) return;
  updateProfil(_profil!.copyWith(username: username));
}
  Future<void> updateInfo({String? groesse, String? gewicht, String? alter, String? geschlecht}) async {
    if (_profil == null) return;
    updateProfil(_profil!.copyWith(
      groesse: groesse,
      gewicht: gewicht,
      alter: alter,
      geschlecht: geschlecht,
    ));
  }

  Future<void> updateImage(String path) async {
    if (_profil == null) return;
    updateProfil(_profil!.copyWith(imagePath: path));
  }
}