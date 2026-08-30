import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import '../models/contact_model.dart';
import '../crud/socialcrud.dart';
import 'add_social.dart';
import '../models/card_container_model.dart';
import '../models/section_title_model.dart';

class SocialPageConstants {
  static const double sectionSpacing = 24;
  static const double contentPadding = 16;
  static const double mediumSpacing = 12;
  static const double smallSpacing = 8;
}

class SocialPage extends StatefulWidget {
  final List<ContactData> contacts;
  final Function(String) onSearchChanged;
  final Function(ContactData) onContactTap;
  final VoidCallback onRefresh;

  const SocialPage({
    super.key,
    required this.contacts,
    required this.onSearchChanged,
    required this.onContactTap,
    required this.onRefresh,
  });

  @override
  State<SocialPage> createState() => _SocialPageViewState();
}

class _SocialPageViewState extends State<SocialPage> {
  int _selectedFilterIndex = 0;

  @override
  Widget build(BuildContext context) {
    List<ContactData> contactsToShow = widget.contacts;

    if (_selectedFilterIndex == 1) {
      contactsToShow = widget.contacts.where((c) => c.type == ChatType.group).toList();
    }

    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.primary,
        iconTheme: IconThemeData(
          color: Theme.of(context).colorScheme.onPrimary,
          size: 40, 
        ),
        leading: IconButton(
          icon: const Icon(Icons.arrow_back),
          onPressed: () => Navigator.of(context).pop(),
        ),
        title: Text(
          "Soziales", 
          style: TextStyle(
            color: Theme.of(context).colorScheme.onPrimary,
            fontSize: 24,
            fontWeight: FontWeight.bold,
          ),
        ),
        centerTitle: false, 
        elevation: 0,
      ),
      
      body: SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.all(SocialPageConstants.contentPadding),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              _buildSearchSection(context),
              const SizedBox(height: SocialPageConstants.sectionSpacing),
              _buildContactListSection(context, contactsToShow),
            ],
          ),
        ),
      ),
    );
  }

  Widget _buildSearchSection(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        const SectionTitleModel(title: 'Suche'),
        const SizedBox(height: SocialPageConstants.mediumSpacing),
        CardContainerModel(
          context: context,
          child: Column(
            children: [
              Row(
                children: [
                  Expanded(
                    child: TextField(
                      onChanged: widget.onSearchChanged,
                      decoration: InputDecoration(
                        prefixIcon: Icon(Icons.search, color: Theme.of(context).colorScheme.primary),
                        hintText: "Freunde durchsuchen",
                        isDense: true,
                        border: InputBorder.none,
                        contentPadding: const EdgeInsets.symmetric(horizontal: 0, vertical: 10),
                      ),
                    ),
                  ),
                  const SizedBox(width: SocialPageConstants.smallSpacing),
                  IconButton(
                    onPressed: () {
                      HapticFeedback.selectionClick();
                      _showAddDialog(context);
                    },
                    icon: Icon(
                      CupertinoIcons.add_circled,
                      size: 30,
                      color: Theme.of(context).colorScheme.primary,
                    ),
                  )
                ],
              ),
              Divider(color: Theme.of(context).colorScheme.onSurface.withOpacity(0.1)),
              const SizedBox(height: SocialPageConstants.smallSpacing),
              SingleChildScrollView(
                scrollDirection: Axis.horizontal,
                child: Row(
                  children: [
                    _buildFilterChip(context, "Alle", 0),
                    _buildFilterChip(context, "Gruppen", 1),
                  ],
                ),
              ),
            ],
          ),
        ),
      ],
    );
  }

  Widget _buildContactListSection(BuildContext context, List<ContactData> contacts) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        const SectionTitleModel(title: 'Nachrichten'),
        const SizedBox(height: SocialPageConstants.mediumSpacing),

        if (contacts.isEmpty)
          CardContainerModel(
            context: context,
            child: const Padding(
              padding: EdgeInsets.all(16.0),
              child: Center(
                child: Text("Keine Chats gefunden."),
              ),
            ),
          )
        else
          CardContainerModel(
            context: context,
            child: ListView.separated(
              shrinkWrap: true,
              physics: const NeverScrollableScrollPhysics(),
              itemCount: contacts.length,
              separatorBuilder: (ctx, i) => Divider(
                height: 1,
                color: Theme.of(context).colorScheme.onSurface.withOpacity(0.1)
              ),
              itemBuilder: (context, index) {
                final contact = contacts[index];
                return ListTile(
                  contentPadding: EdgeInsets.zero,
                  leading: CircleAvatar(
                    backgroundColor: Theme.of(context).colorScheme.primary.withAlpha(30),
                    child: Icon(
                      contact.type == ChatType.group ? Icons.groups : Icons.person,
                      color: Theme.of(context).colorScheme.primary,
                      size: 20,
                    ),
                  ),
                  title: Text(
                    contact.username,
                    style: const TextStyle(fontWeight: FontWeight.w600),
                  ),
                  subtitle: Text(
                    contact.type == ChatType.group 
                        ? "${contact.members.length} Mitglieder" 
                        : "Klicke zum Chatten",
                    style: TextStyle(fontSize: 12, color: Colors.grey[600]),
                  ),
                  trailing: Text(
                    _formatTime(contact.lastMessageTime),
                    style: TextStyle(
                      color: Theme.of(context).colorScheme.primary,
                      fontWeight: FontWeight.bold,
                      fontSize: 12,
                    ),
                  ),
                  onTap: () => widget.onContactTap(contact),
                );
              },
            ),
          ),
      ],
    );
  }

  Widget _buildFilterChip(BuildContext context, String label, int index) {
    final bool isSelected = _selectedFilterIndex == index;
    return Padding(
      padding: const EdgeInsets.only(right: 8.0),
      child: GestureDetector(
        onTap: () {
          HapticFeedback.selectionClick();
          setState(() {
            _selectedFilterIndex = index;
          });
        },
        child: Container(
          padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
          decoration: BoxDecoration(
            color: isSelected
                ? Theme.of(context).colorScheme.primary
                : Theme.of(context).colorScheme.primary.withAlpha(20),
            borderRadius: BorderRadius.circular(20),
          ),
          child: Text(
            label,
            style: TextStyle(
              color: isSelected ? Colors.white : Theme.of(context).colorScheme.primary,
              fontWeight: FontWeight.w600,
              fontSize: 12,
            ),
          ),
        ),
      ),
    );
  }

  String _formatTime(DateTime time) {
    final now = DateTime.now();
    final today = DateTime(now.year, now.month, now.day);
    final dateToCheck = DateTime(time.year, time.month, time.day);

    if (dateToCheck == today) {
      return "${time.hour.toString().padLeft(2, '0')}:${time.minute.toString().padLeft(2, '0')}";
    } else if (dateToCheck == today.subtract(const Duration(days: 1))) {
      return "Gestern";
    } else {
      return "${time.day}.${time.month}.";
    }
  }

  void _showAddDialog(BuildContext context) {
    showDialog(
      context: context,
      builder: (ctx) => AlertDialog(
        contentPadding: const EdgeInsets.symmetric(vertical: 20),
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            ListTile(
              leading: Icon(Icons.person_add, color: Theme.of(context).colorScheme.primary),
              title: const Text("Freund hinzufügen"),
              onTap: () async {
                Navigator.pop(ctx);
                await Navigator.push(
                  context,
                  MaterialPageRoute(builder: (_) => AddFriendScreen(crud: SocialCrud()))
                );
                widget.onRefresh();
              },
            ),
            Divider(color: Colors.grey[300]),
            ListTile(
              leading: Icon(Icons.group_add, color: Theme.of(context).colorScheme.primary),
              title: const Text("Gruppe erstellen"),
              onTap: () async {
                Navigator.pop(ctx);
                await Navigator.push(
                  context,
                  MaterialPageRoute(builder: (_) => CreateGroupScreen(crud: SocialCrud()))
                );
                widget.onRefresh();
              },
            ),
          ],
        ),
      ),
    );
  }
}