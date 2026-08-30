import 'package:flutter/material.dart';
import 'package:src/handler/chat_handler.dart';
import '../crud/socialcrud.dart';
import '../models/contact_model.dart';
import '../pages/social.dart'; 

class SocialPageHandler extends StatefulWidget {
  const SocialPageHandler({super.key});

  @override
  State<SocialPageHandler> createState() => _SocialPageHandlerState();
}

class _SocialPageHandlerState extends State<SocialPageHandler> {
  final _crud = SocialCrud();
  
  List<ContactData> _allContacts = []; 
  List<ContactData> _filteredContacts = []; 
  
  bool _isLoading = true;

  @override
  void initState() {
    super.initState();
    _loadData();
  }

  Future<void> _loadData() async {
    final loaded = await _crud.getContacts();
    
    loaded.sort((a, b) => b.lastMessageTime.compareTo(a.lastMessageTime));

    if (mounted) {
      setState(() {
        _allContacts = loaded;
        _filteredContacts = loaded; 
        _isLoading = false;
      });
    }
  }

  void _runFilter(String enteredKeyword) {
    List<ContactData> results = [];
    if (enteredKeyword.isEmpty) {
      results = _allContacts;
    } else {
      results = _allContacts
          .where((user) => user.username.toLowerCase().contains(enteredKeyword.toLowerCase()))
          .toList();
    }

    setState(() {
      _filteredContacts = results;
    });
  }

  @override
  Widget build(BuildContext context) {
    if (_isLoading) {
      return const Scaffold(body: Center(child: CircularProgressIndicator()));
    }

    return SocialPage(
      contacts: _filteredContacts,
      onSearchChanged: _runFilter,
      onContactTap: (contact) async {
        await Navigator.push(
          context,
          MaterialPageRoute(
            builder: (context) => ChatHandler(contactName: contact.username),
          ),
        );
      
      _loadData();
      },

      onRefresh: _loadData,
    );
  }
}