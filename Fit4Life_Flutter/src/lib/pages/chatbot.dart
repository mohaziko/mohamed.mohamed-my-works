import 'package:flutter/material.dart';
import 'package:flutter/cupertino.dart';
import '../models/chat_model.dart'; // Pfad ggf. anpassen
import '../models/card_container_model.dart'; // Pfad ggf. anpassen

class ChatbotPage extends StatefulWidget {
  const ChatbotPage({super.key});

  @override
  State<ChatbotPage> createState() => _ChatbotPageState();
}

class _ChatbotPageState extends State<ChatbotPage> {
  final TextEditingController _textController = TextEditingController();
  final ScrollController _scrollController = ScrollController();
  
  // Start-Nachricht vom KI-Assistenten
  final List<ChatMessage> _messages = [
    ChatMessage(
      text: "Hallo! Ich bin dein KI-Assistent für Ernährung und Fitness. Wie kann ich dir heute helfen?",
      time: DateTime.now(),
      isMe: false, // false = Nachricht vom Assistenten
    ),
  ];

  // Die feste Antwort
  final String _mockResponse = "Das ist eine sehr interessante Frage! Da ich momentan noch ein Prototyp bin, kann ich leider keine spezifische Auskunft dazu geben. Aber bleib dran, bald lerne ich mehr!";

  void _handleSend() {
    final text = _textController.text.trim();
    if (text.isEmpty) return;

    setState(() {
      // 1. Deine Nachricht hinzufügen
      _messages.add(ChatMessage(
        text: text,
        time: DateTime.now(),
        isMe: true,
      ));
      _textController.clear();
    });

    _scrollToBottom();

    // 2. Antwort simulieren (nach 1 Sekunde Wartezeit)
    Future.delayed(const Duration(seconds: 1), () {
      if (!mounted) return;
      setState(() {
        _messages.add(ChatMessage(
          text: _mockResponse,
          time: DateTime.now(),
          isMe: false,
        ));
      });
      _scrollToBottom();
    });
  }

  void _scrollToBottom() {
    // Kurze Verzögerung, damit die Liste Zeit hat sich aufzubauen
    Future.delayed(const Duration(milliseconds: 100), () {
      if (_scrollController.hasClients) {
        _scrollController.animateTo(
          _scrollController.position.maxScrollExtent,
          duration: const Duration(milliseconds: 300),
          curve: Curves.easeOut,
        );
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    final primaryColor = Theme.of(context).colorScheme.primary;
    final onPrimaryColor = Theme.of(context).colorScheme.onPrimary;

    return Scaffold(
      // --- APP BAR (Blaues Design wie Profil/Social) ---
      appBar: AppBar(
        backgroundColor: primaryColor,
        iconTheme: IconThemeData(
          color: onPrimaryColor,
          size: 40,
        ),
        leading: IconButton(
          icon: const Icon(Icons.arrow_back),
          onPressed: () => Navigator.pop(context),
        ),
        title: Row(
          mainAxisSize: MainAxisSize.min,
          children: [
            CircleAvatar(
              radius: 16,
              backgroundColor: onPrimaryColor,
              child: Icon(Icons.auto_awesome, size: 20, color: primaryColor), // KI Icon
            ),
            const SizedBox(width: 10),
            Text(
              "KI Assistent",
              style: TextStyle(
                fontSize: 24,
                fontWeight: FontWeight.bold,
                color: onPrimaryColor,
              ),
            ),
          ],
        ),
        centerTitle: true,
        elevation: 0,
      ),
      
      body: Column(
        children: [
          // --- CHAT VERLAUF ---
          Expanded(
            child: ListView.builder(
              controller: _scrollController,
              padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 10),
              itemCount: _messages.length,
              itemBuilder: (context, index) {
                final msg = _messages[index];
                return _buildChatBubble(context, msg);
              },
            ),
          ),

          // --- EINGABEBEREICH ---
          _buildInputArea(context),
        ],
      ),
    );
  }

  // Identisch zum Design in ChatPage
  Widget _buildChatBubble(BuildContext context, ChatMessage msg) {
    final primaryColor = Theme.of(context).colorScheme.primary;
    final isMe = msg.isMe;

    return Align(
      alignment: isMe ? Alignment.centerRight : Alignment.centerLeft,
      child: Container(
        margin: const EdgeInsets.symmetric(vertical: 4),
        padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 10),
        constraints: const BoxConstraints(maxWidth: 280),
        decoration: BoxDecoration(
          color: isMe ? primaryColor : primaryColor.withAlpha(20),
          borderRadius: BorderRadius.only(
            topLeft: const Radius.circular(20),
            topRight: const Radius.circular(20),
            bottomLeft: isMe ? const Radius.circular(20) : const Radius.circular(4),
            bottomRight: isMe ? const Radius.circular(4) : const Radius.circular(20),
          ),
        ),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.end,
          children: [
            Text(
              msg.text,
              style: TextStyle(
                color: isMe ? Colors.white : Colors.black87,
                fontSize: 16,
              ),
            ),
            const SizedBox(height: 4),
            Text(
              "${msg.time.hour}:${msg.time.minute.toString().padLeft(2, '0')}",
              style: TextStyle(
                color: isMe ? Colors.white.withOpacity(0.7) : Colors.black54,
                fontSize: 10,
                fontWeight: FontWeight.w500
              ),
            )
          ],
        ),
      ),
    );
  }

  // Identisch zum Design in ChatPage
  Widget _buildInputArea(BuildContext context) {
    return SafeArea(
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: CardContainerModel(
          context: context,
          child: Row(
            children: [
              Expanded(
                child: TextField(
                  controller: _textController,
                  decoration: const InputDecoration(
                    hintText: "Frag etwas...",
                    border: InputBorder.none,
                    isDense: true,
                    contentPadding: EdgeInsets.symmetric(horizontal: 4, vertical: 8),
                  ),
                  onSubmitted: (_) => _handleSend(),
                ),
              ),
              const SizedBox(width: 8),
              IconButton(
                icon: Icon(
                  CupertinoIcons.arrow_up_circle_fill,
                  color: Theme.of(context).colorScheme.primary,
                  size: 32,
                ),
                padding: EdgeInsets.zero,
                constraints: const BoxConstraints(),
                onPressed: _handleSend,
              ),
            ],
          ),
        ),
      ),
    );
  }
}