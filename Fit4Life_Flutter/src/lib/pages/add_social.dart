import 'package:flutter/material.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/services.dart';
import '../models/contact_model.dart';
import '../crud/socialcrud.dart'; 
import '../models/card_container_model.dart';
import '../models/section_title_model.dart';

class AddScreenConstants {
  static const double sectionSpacing = 24;
  static const double contentPadding = 16;
  static const double mediumSpacing = 12;
}

class AddFriendScreen extends StatefulWidget {
  final SocialCrud crud;
  const AddFriendScreen({super.key, required this.crud});

  @override
  State<AddFriendScreen> createState() => _AddFriendScreenState();
}

class _AddFriendScreenState extends State<AddFriendScreen> {
  late List<ContactData> _allUsers;
  List<ContactData> _filteredUsers = [];

  @override
  void initState() {
    super.initState();
    _allUsers = widget.crud.getPotentialUsers();
    _filteredUsers = _allUsers;
  }

  void _runFilter(String keyword) {
    setState(() {
      if (keyword.isEmpty) {
        _filteredUsers = _allUsers;
      } else {
        _filteredUsers = _allUsers
            .where((user) => user.username.toLowerCase().contains(keyword.toLowerCase()))
            .toList();
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.primary,
        iconTheme: IconThemeData(
          color: Theme.of(context).colorScheme.onPrimary,
          size: 40,
        ),
        leading: IconButton(
          icon: const Icon(Icons.arrow_back),
          onPressed: () => Navigator.pop(context),
        ),
        title: Text(
          "Freunde finden",
          style: TextStyle(
            color: Theme.of(context).colorScheme.onPrimary, 
            fontSize: 24,
            fontWeight: FontWeight.bold
          ),
        ),
        elevation: 0,
      ),
      
      body: SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.all(AddScreenConstants.contentPadding),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              const SectionTitleModel(title: 'Suche'),
              const SizedBox(height: AddScreenConstants.mediumSpacing),
              CardContainerModel(
                context: context,
                child: TextField(
                  onChanged: _runFilter,
                  decoration: InputDecoration(
                    prefixIcon: Icon(Icons.search, color: Theme.of(context).colorScheme.primary),
                    hintText: "Namen eingeben...",
                    border: InputBorder.none,
                    isDense: true,
                    contentPadding: const EdgeInsets.symmetric(vertical: 12),
                  ),
                ),
              ),
              const SizedBox(height: AddScreenConstants.sectionSpacing),
              const SectionTitleModel(title: 'Vorschläge'),
              const SizedBox(height: AddScreenConstants.mediumSpacing),
              
              if (_filteredUsers.isEmpty)
                Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: Text("Keine Nutzer gefunden.", style: TextStyle(color: Colors.grey[600])),
                )
              else
                CardContainerModel(
                  context: context,
                  child: ListView.separated(
                    shrinkWrap: true,
                    physics: const NeverScrollableScrollPhysics(),
                    itemCount: _filteredUsers.length,
                    separatorBuilder: (ctx, i) => Divider(
                      height: 1, 
                      color: Theme.of(context).colorScheme.onSurface.withOpacity(0.1)
                    ),
                    itemBuilder: (context, index) {
                      final contact = _filteredUsers[index];
                      final name = contact.username;
                      return ListTile(
                        contentPadding: EdgeInsets.zero,
                        leading: CircleAvatar(
                          backgroundColor: Theme.of(context).colorScheme.primary.withAlpha(30),
                          child: Icon(Icons.person_outline, color: Theme.of(context).colorScheme.primary),
                        ),
                        title: Text(name, style: const TextStyle(fontWeight: FontWeight.w500)),
                        trailing: IconButton(
                          icon: Icon(CupertinoIcons.add_circled, color: Theme.of(context).colorScheme.primary),
                          onPressed: () {
                            HapticFeedback.selectionClick();
                            _addFriend(contact);
                          },
                        ),
                      );
                    },
                  ),
                ),
            ],
          ),
        ),
      ),
    );
  }

  void _addFriend(ContactData potentialFriend) {
    final newFriend = ContactData(
      username: potentialFriend.username,
      score: potentialFriend.score,
      lastMessageTime: DateTime.now(),
      isOnline: potentialFriend.isOnline,
      type: ChatType.single,
    );
    
    widget.crud.saveContact(newFriend).then((_) {
      if (!mounted) return;
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(
          content: Text("${potentialFriend.username} hinzugefügt!"),
          behavior: SnackBarBehavior.floating,
          shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(10)),
          backgroundColor: Theme.of(context).colorScheme.primary,
        )
      );
    });
  }
}

class CreateGroupScreen extends StatefulWidget {
  final SocialCrud crud;
  const CreateGroupScreen({super.key, required this.crud});

  @override
  State<CreateGroupScreen> createState() => _CreateGroupScreenState();
}

class _CreateGroupScreenState extends State<CreateGroupScreen> {
  final _nameController = TextEditingController();
  List<ContactData> _myFriends = [];
  final List<String> _selectedMembers = [];

  @override
  void initState() {
    super.initState();
    _loadFriends();
  }

  Future<void> _loadFriends() async {
    final friends = await widget.crud.getContacts();
    setState(() {
      _myFriends = friends.where((c) => c.type == ChatType.single).toList();
    });
  }

  void _createGroup() async {
    if (_nameController.text.isEmpty) return;
    if (_selectedMembers.isEmpty) {
       ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text("Wähle mindestens ein Mitglied")));
       return;
    }

    final newGroup = ContactData(
      username: _nameController.text,
      lastMessageTime: DateTime.now(),
      type: ChatType.group,
      members: _selectedMembers,
      isPrivate: false,
    );

    await widget.crud.saveContact(newGroup);

    if (!mounted) return;
    Navigator.pop(context);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.primary,
        iconTheme: IconThemeData(
          color: Theme.of(context).colorScheme.onPrimary,
          size: 40,
        ),
        leading: IconButton(
          icon: const Icon(Icons.close),
          onPressed: () => Navigator.pop(context),
        ),
        title: Text(
          "Neue Gruppe",
          style: TextStyle(
            color: Theme.of(context).colorScheme.onPrimary,
            fontSize: 24,
            fontWeight: FontWeight.bold
          ),
        ),
        elevation: 0,
        actions: [
          TextButton(
            onPressed: () {
              HapticFeedback.selectionClick();
              _createGroup();
            },
            child: Text(
              "Erstellen",
              style: TextStyle(
                color: Theme.of(context).colorScheme.onPrimary, 
                fontWeight: FontWeight.bold, 
                fontSize: 16
              ),
            ),
          )
        ],
      ),
      
      body: SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.all(AddScreenConstants.contentPadding),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              const SectionTitleModel(title: 'Details'),
              const SizedBox(height: AddScreenConstants.mediumSpacing),
              CardContainerModel(
                context: context,
                child: Column(
                  children: [
                    TextField(
                      controller: _nameController,
                      style: const TextStyle(fontWeight: FontWeight.bold),
                      decoration: InputDecoration(
                        prefixIcon: Icon(Icons.groups, color: Theme.of(context).colorScheme.primary),
                        hintText: "Gruppenname",
                        border: InputBorder.none,
                        contentPadding: const EdgeInsets.symmetric(vertical: 14),
                      ),
                    ),
                  ],
                ),
              ),
              const SizedBox(height: AddScreenConstants.sectionSpacing),
              const SectionTitleModel(title: 'Mitglieder auswählen'),
              const SizedBox(height: AddScreenConstants.mediumSpacing),

              if (_myFriends.isEmpty)
                CardContainerModel(
                  context: context,
                  child: const Padding(
                    padding: EdgeInsets.all(16.0),
                    child: Center(child: Text("Du hast noch keine Freunde hinzugefügt.")),
                  ),
                )
              else
                CardContainerModel(
                  context: context,
                  child: ListView.separated(
                    shrinkWrap: true,
                    physics: const NeverScrollableScrollPhysics(),
                    itemCount: _myFriends.length,
                    separatorBuilder: (ctx, i) => Divider(
                      height: 1, 
                      color: Theme.of(context).colorScheme.onSurface.withOpacity(0.1)
                    ),
                    itemBuilder: (context, index) {
                      final friend = _myFriends[index];
                      final isSelected = _selectedMembers.contains(friend.username);
                      
                      return CheckboxListTile(
                        title: Text(friend.username, style: const TextStyle(fontWeight: FontWeight.w500)),
                        value: isSelected,
                        activeColor: Theme.of(context).colorScheme.primary,
                        contentPadding: EdgeInsets.zero,
                        secondary: CircleAvatar(
                          backgroundColor: Theme.of(context).colorScheme.primary.withAlpha(30),
                          child: Icon(Icons.person, color: Theme.of(context).colorScheme.primary, size: 20),
                        ),
                        onChanged: (val) {
                          HapticFeedback.selectionClick();
                          setState(() {
                            if (val == true) {
                              _selectedMembers.add(friend.username);
                            } else {
                              _selectedMembers.remove(friend.username);
                            }
                          });
                        },
                      );
                    },
                  ),
                ),
            ],
          ),
        ),
      ),
    );
  }
}