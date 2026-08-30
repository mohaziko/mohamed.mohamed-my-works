import 'dart:io';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:image_picker/image_picker.dart';
import 'package:qr_flutter/qr_flutter.dart';
import 'package:src/main.dart';
import 'package:src/models/info_bar_model.dart';
import 'package:url_launcher/url_launcher.dart';
import '../handler/profile_handler.dart';
import 'package:share_plus/share_plus.dart';

class ProfilPage extends StatefulWidget {
  const ProfilPage({super.key});

  @override
  State<ProfilPage> createState() => _ProfilPageState();
}

class _ProfilPageState extends State<ProfilPage> {
  final Color primaryColor = const Color(0xFF2E5B8A);
  final Color backgroundColor = Colors.white;
  final Color cardColor = const Color(0xFFE5E7EB);
  final ImagePicker _picker = ImagePicker();

  @override
  void initState() {
    super.initState();
    WidgetsBinding.instance.addPostFrameCallback((_) {
      context.read<ProfilHandler>().loadProfil();
    });
  }

  Future<void> _pickImage(ProfilHandler handler) async {
  showModalBottomSheet(
    context: context,
    shape: const RoundedRectangleBorder(
      borderRadius: BorderRadius.vertical(top: Radius.circular(20)),
    ),
    builder: (context) => SafeArea(
      child: Wrap(
        children: [
          const Padding(
            padding: EdgeInsets.all(16.0),
            child: Text(
              "Profilbild auswählen",
              style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
            ),
          ),
          ListTile(
            leading: const Icon(Icons.camera_alt, color: Color(0xFF2E5B8A)),
            title: const Text('Kamera öffnen'),
            onTap: () async {
              Navigator.pop(context);
              final XFile? image = await _picker.pickImage(
                source: ImageSource.camera,
                preferredCameraDevice: CameraDevice.rear,
              );
              if (image != null) {
                handler.updateImage(image.path);
              }
            },
          ),
          ListTile(
            leading: const Icon(Icons.photo_library, color: Color(0xFF2E5B8A)),
            title: const Text('Aus Galerie wählen'),
            onTap: () async {
              Navigator.pop(context);
              final XFile? image = await _picker.pickImage(
                source: ImageSource.gallery,
                imageQuality: 80,
              );
              if (image != null) {
                handler.updateImage(image.path);
              }
            },
          ),
          const SizedBox(height: 12),
        ],
      ),
    ),
  );
}

  void _showEditNameDialog(ProfilHandler handler, String currentName) {
    final controller = TextEditingController(text: currentName);
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text("Name bearbeiten"),
        content: TextField(
          controller: controller,
          decoration: const InputDecoration(hintText: "Dein Name"),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.pop(context), child: const Text("Abbrechen")),
          ElevatedButton(
            onPressed: () {
              handler.updateName(controller.text);
              Navigator.pop(context);
            },
            child: const Text("Speichern"),
          ),
        ],
      ),
    );
  }

  void _showEditUsernameDialog(ProfilHandler handler, String currentUsername) {
    final controller = TextEditingController(text: currentUsername);
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text("Username bearbeiten"),
        content: TextField(
          controller: controller,
          decoration: const InputDecoration(hintText: "Dein Username", prefixText: "@"),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.pop(context), child: const Text("Abbrechen")),
          ElevatedButton(
            onPressed: () {
              handler.updateUsername(controller.text);
              Navigator.pop(context);
            },
            child: const Text("Speichern"),
          ),
        ],
      ),
    );
  }
  void _showEditInfoDialog(ProfilHandler handler, String label, String currentValue, String field) {
    final controller = TextEditingController(text: currentValue);
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: Text("$label bearbeiten"),
        content: TextField(
          controller: controller,
          keyboardType: field == 'geschlecht' ? TextInputType.text : TextInputType.number,
          decoration: InputDecoration(hintText: label),
        ),
        actions: [
          TextButton(onPressed: () => Navigator.pop(context), child: const Text("Abbrechen")),
          ElevatedButton(
            onPressed: () {
              if (field == 'groesse') handler.updateInfo(groesse: controller.text);
              if (field == 'gewicht') handler.updateInfo(gewicht: controller.text);
              if (field == 'alter') handler.updateInfo(alter: controller.text);
              if (field == 'geschlecht') handler.updateInfo(geschlecht: controller.text);
              Navigator.pop(context);
            },
            child: const Text("Speichern"),
          ),
        ],
      ),
    );
  }

  void _showQrDialog(String name, String username) {
    showDialog(
      context: context,
      builder: (context) => Dialog(
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
        child: Padding(
          padding: const EdgeInsets.all(24.0),
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              Text(name, style: const TextStyle(fontSize: 20, fontWeight: FontWeight.bold)),
              const SizedBox(height: 20),
              SizedBox(
                width: 200,
                height: 200,
                child: QrImageView(
                  data: "Benutzer: $name\nBenutzername: $username",
                  version: QrVersions.auto,
                  size: 200.0,
                ),
              ),
              const SizedBox(height: 24),
              Row(
                children: [
                  Expanded(
                    child: TextButton(
                      onPressed: () => Navigator.pop(context),
                      child: const Text("Schließen"),
                    ),
                  ),
                  const SizedBox(width: 8),
                  Expanded(
                    child: ElevatedButton.icon(
                      onPressed: () {
                        SharePlus.instance.share(
                          ShareParams(
                            text:
                            'Scan meinen QR-Code in Fit4Life! \nBenutzername: $username',
                            subject: 'Mein Profil teilen',
                          ),
                        );
                      },
                      icon: Icon(Icons.adaptive.share, size: 18),
                      label: const Text("Teilen"),
                      style: ElevatedButton.styleFrom(
                        backgroundColor: primaryColor,
                        foregroundColor: Colors.white,
                        shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(12)),
                      ),
                    ),
                  ),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: backgroundColor,
      appBar: AppBar(
        backgroundColor: primaryColor,
        elevation: 4,
        leading: IconButton(
          icon: const Icon(Icons.arrow_back, color: Colors.white),
          onPressed: () => Navigator.maybePop(context),
        ),
        title: const Text("Mein Profil", style: TextStyle(color: Colors.white, fontWeight: FontWeight.bold)),
        actions: [
          Consumer<ProfilHandler>(
            builder: (context, handler, _) => IconButton(
              icon: const Icon(Icons.qr_code, color: Colors.white),
              onPressed: () => _showQrDialog(handler.profil?.name ?? "user", handler.profil?.username ?? "username_unbekannt"),
            ),
          ),
        ],
      ),
      body: Consumer<ProfilHandler>(
        builder: (context, handler, child) {
          if (handler.isLoading) return const Center(child: CircularProgressIndicator());
          if (handler.profil == null) return const Center(child: Text("Kein Profil gefunden"));

          final profil = handler.profil!;
          return SingleChildScrollView(
            child: Column(
              children: [
                _buildProfileHeader(handler, profil.name, profil.imagePath),
                _buildInfoSection(handler, profil.groesse, profil.gewicht, profil.alter, profil.geschlecht),
                _buildSettingsSection(handler),
                _buildOtherSection(),
                _buildResetSection(),
                const SizedBox(height: 32),
              ],
            ),
          );
        },
      ),
    );
  }

  Widget _buildProfileHeader(ProfilHandler handler, String name, String? imagePath) {
    final String username = handler.profil?.username ?? "username_unbekannt";
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 32),
      child: Column(
        children: [
          GestureDetector(
            onTap: () => _pickImage(handler),
            child: Stack(
              children: [
                Container(
                  width: 100,
                  height: 100,
                  decoration: BoxDecoration(
                    color: Colors.blue[50],
                    shape: BoxShape.circle,
                    border: Border.all(color: Colors.white, width: 4),
                    boxShadow: [BoxShadow(color: Colors.black.withAlpha(13), blurRadius: 10, offset: const Offset(0, 4))],
                  ),
                  child: ClipOval(
                    child: (imagePath != null && File(imagePath).existsSync())
                        ? Image.file(File(imagePath), fit: BoxFit.cover)
                        : Icon(Icons.person, size: 50, color: primaryColor),
                  ),
                ),
                Positioned(
                  bottom: 0,
                  right: 0,
                  child: Container(
                    padding: const EdgeInsets.all(6),
                    decoration: const BoxDecoration(color: Colors.white, shape: BoxShape.circle),
                    child: Icon(Icons.camera_alt, size: 16, color: primaryColor),
                  ),
                ),
              ],
            ),
          ),
          const SizedBox(height: 16),
          GestureDetector(
            onTap: () => _showEditNameDialog(handler, name),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Text(name, style: const TextStyle(fontSize: 24, fontWeight: FontWeight.bold, color: Color(0xFF1F2937))),
                const SizedBox(width: 8),
                Icon(Icons.edit, size: 18, color: Colors.grey[400]),
              ],
            ),
          ),
          const SizedBox(height: 4),
          GestureDetector(
            onTap: () => _showEditUsernameDialog(handler, username),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Text(
                  "@$username",
                  style: TextStyle(
                    fontSize: 14,
                    color: Colors.grey[600],
                    fontWeight: FontWeight.w400,
                  ),
                ),
                const SizedBox(width: 4),
                Icon(Icons.edit, size: 12, color: Colors.grey[400]),
              ],
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildInfoSection(ProfilHandler handler, String groesse, String gewicht, String alter, String geschlecht) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
      child: Container(
        padding: const EdgeInsets.symmetric(vertical: 24),
        decoration: BoxDecoration(color: cardColor, borderRadius: BorderRadius.circular(20)),
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: [
            _infoItem(handler, "$groesse cm", "Größe", groesse, 'groesse'),
            Container(width: 1, height: 48, color: Colors.grey[300]),
            _infoItem(handler, "$gewicht kg", "Gewicht", gewicht, 'gewicht'),
            Container(width: 1, height: 48, color: Colors.grey[300]),
            _infoItem(handler, "$alter Jahre", "Alter", alter, 'alter'),
            Container(width: 1, height: 48, color: Colors.grey[300]),
            _infoItem(handler, geschlecht, "Geschlecht", geschlecht, 'geschlecht'),
          ],
        ),
      ),
    );
  }

  Widget _infoItem(ProfilHandler handler, String value, String label, String rawValue, String field) {
    return GestureDetector(
      onTap: () => _showEditInfoDialog(handler, label, rawValue, field),
      child: Column(
        children: [
          Text(value, style: const TextStyle(fontSize: 18, fontWeight: FontWeight.bold, color: Color(0xFF1F2937))),
          Text(label, style: const TextStyle(fontSize: 12, color: Colors.grey, fontWeight: FontWeight.w500)),
        ],
      ),
    );
  }

  Widget _buildSettingsSection(ProfilHandler handler) {
    return Padding(
      padding: const EdgeInsets.all(16),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          const SectionHeader(title: "EINSTELLUNGEN"),
          Container(
            decoration: BoxDecoration(
              color: cardColor, 
              borderRadius: BorderRadius.circular(20),
            ),
            child: ListTile(
              leading: Icon(Icons.notifications_none, color: primaryColor),
              title: const Text("Push-Benachrichtigungen", style: TextStyle(fontWeight: FontWeight.w500)),
              trailing: Switch(
                value: handler.profil!.pushEnabled,
                onChanged: (val) => handler.updatePushEnabled(val),
                activeThumbColor: primaryColor,
              ),
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildOtherSection() {
    return Padding(
      padding: const EdgeInsets.all(16),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          const SectionHeader(title: "ANDERES"),
          Container(
            decoration: BoxDecoration(
              color: cardColor, 
              borderRadius: BorderRadius.circular(20),
            ),
            child: Column(
              children: [
                _buildListItem(Icons.mail_outline, "Kontaktieren Sie uns", () async {
                  final Uri url = Uri.parse('https://h-da.de/');
                  if (await canLaunchUrl(url)) {
                    await launchUrl(url);
                  }
                }),
                Divider(height: 1, indent: 56, color: Colors.grey[100]),
                _buildListItem(Icons.shield_outlined, "Datenschutzrichtlinien", () async {
                  final Uri url = Uri.parse('https://h-da.de/');
                  if (await canLaunchUrl(url)) {
                    await launchUrl(url);
                  }
                }),
              ],
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildListItem(IconData icon, String title, [VoidCallback? onTap]) {
    return ListTile(
      leading: Icon(icon, color: primaryColor),
      title: Text(title, style: const TextStyle(fontWeight: FontWeight.w500)),
      trailing: const Icon(Icons.chevron_right, color: Colors.grey),
      onTap: onTap ?? () {},
    );
  }

  Widget _buildResetSection() {
    return Padding(
      padding: const EdgeInsets.all(16),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          const SectionHeader(title: "DATEN ZURÜCKSETZEN"),
          Container(
            decoration: BoxDecoration(
              color: cardColor,
              borderRadius: BorderRadius.circular(20),
            ),
            child: ListTile(
              leading: Icon(Icons.delete_forever, color: Colors.red),
              title: const Text("Alle Daten Zurücksetzen", style: TextStyle(fontWeight: FontWeight.w500, color: Colors.red)),
              onTap: () => _showResetConfirmationDialog(),
            ),
          ),
        ],
      ),
    );
  }

  void _showResetConfirmationDialog() {
    final parentContext = context;
    showDialog(
      context: parentContext,
      builder: (dialogContext) => AlertDialog(
        title: const Text("Alle Daten löschen?"),
        content: const Text(
          "Diese Aktion löscht alle gespeicherten Daten (Profile, Essen, Training, etc.). "
          "Diese Aktion kann nicht rückgängig gemacht werden."
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(dialogContext),
            child: const Text("Abbrechen"),
          ),
          ElevatedButton(
            onPressed: () async {
              await clearAllHiveData();
              parentContext.read<ProfilHandler>().loadProfil();
              Navigator.pop(dialogContext);
              showInfoBar(parentContext, "Alle Daten wurden gelöscht");
            },
            style: ElevatedButton.styleFrom(backgroundColor: Colors.red),
            child: const Text("Löschen", style: TextStyle(color: Colors.white)),
          ),
        ],
      ),
    );
  }
}

class SectionHeader extends StatelessWidget {
  final String title;
  const SectionHeader({super.key, required this.title});
  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 8),
      child: Text(title, style: const TextStyle(fontSize: 12, fontWeight: FontWeight.bold, color: Colors.grey, letterSpacing: 1.2)),
    );
  }
}