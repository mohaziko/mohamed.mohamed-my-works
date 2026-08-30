import 'package:flutter/material.dart';
import '../models/chat_model.dart';
import '../pages/chat.dart';
import '../crud/socialcrud.dart'; 

class ChatHandler extends StatefulWidget {
  final String contactName;

  const ChatHandler({super.key, required this.contactName});

  @override
  State<ChatHandler> createState() => _ChatHandlerState();
}

class _ChatHandlerState extends State<ChatHandler> {
  final _crud = SocialCrud(); 
  List<ChatMessage> _messages = [];
  
  final TextEditingController _textController = TextEditingController();
  final ScrollController _scrollController = ScrollController();
  bool _isLoading = true;

  @override
  void initState() {
    super.initState();
    _loadMessages();
  }

  Future<void> _loadMessages() async {
    final loaded = await _crud.getChatHistory(widget.contactName);
    
    if (mounted) {
      setState(() {
        _messages = loaded;
        _isLoading = false;
      });
      Future.delayed(const Duration(milliseconds: 100), _scrollToBottom);
    }
  }

  void _saveToDb() {
    _crud.saveChatHistory(widget.contactName, _messages);
  }

  void _handleSendMessage() {
    final text = _textController.text;
    if (text.trim().isEmpty) return;

    final now = DateTime.now();

    setState(() {
      _messages.add(ChatMessage(
        text: text,
        time: now,
        isMe: true,
      ));
      _textController.clear();
    });
    
    _saveToDb(); 

    _crud.updateContactTime(widget.contactName, now);

    _scrollToBottom();

    _simulateAutoReply();
  }

  Future<void> _simulateAutoReply() async {
    await Future.delayed(const Duration(seconds: 1));
    final now = DateTime.now();

    if (mounted) {
      setState(() {
        _messages.add(ChatMessage(
          text: "Auto-Antwort von ${widget.contactName}",
          time: now,
          isMe: false,
        ));
      });
      
      _saveToDb(); 

      _crud.updateContactTime(widget.contactName, now);

      _scrollToBottom();
    }
  }

  void _scrollToBottom() {
    if (_scrollController.hasClients) {
      _scrollController.animateTo(
        _scrollController.position.maxScrollExtent,
        duration: const Duration(milliseconds: 300),
        curve: Curves.easeOut,
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    if (_isLoading) {
      return Scaffold(
        appBar: AppBar(title: Text(widget.contactName)),
        body: const Center(child: CircularProgressIndicator()),
      );
    }

    return ChatPage(
      contactName: widget.contactName,
      messages: _messages,
      textController: _textController,
      onSendPressed: _handleSendMessage,
      scrollController: _scrollController,
    );
  }
}