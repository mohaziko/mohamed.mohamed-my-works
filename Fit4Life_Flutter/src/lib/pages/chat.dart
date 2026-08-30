import 'package:flutter/material.dart';
import 'package:flutter/cupertino.dart';
import '../models/chat_model.dart';
import '../models/card_container_model.dart'; 

class ChatPage extends StatelessWidget {
  final String contactName;
  final List<ChatMessage> messages;
  final TextEditingController textController;
  final VoidCallback onSendPressed;
  final ScrollController scrollController;

  const ChatPage({
    super.key,
    required this.contactName,
    required this.messages,
    required this.textController,
    required this.onSendPressed,
    required this.scrollController,
  });

  @override
  Widget build(BuildContext context) {
    final primaryColor = Theme.of(context).colorScheme.primary;
    final onPrimaryColor = Theme.of(context).colorScheme.onPrimary;

    return Scaffold(
      // --- NEUES APP BAR DESIGN ---
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
              // Wir machen den Hintergrund weiß, damit das Icon in Primary Color wirkt
              backgroundColor: onPrimaryColor,
              child: Icon(Icons.person, size: 20, color: primaryColor),
            ),
            const SizedBox(width: 10),
            Text(
              contactName,
              style: TextStyle(
                fontSize: 24, // Größe angepasst an Profil
                fontWeight: FontWeight.bold,
                color: onPrimaryColor, // Wichtig: Weißer Text auf blauem Grund
              ),
            ),
          ],
        ),
        centerTitle: true,
        elevation: 0,
      ),
      // ----------------------------
      
      body: Column(
        children: [
          Expanded(
            child: ListView.builder(
              controller: scrollController,
              padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 10),
              itemCount: messages.length,
              itemBuilder: (context, index) {
                final msg = messages[index];
                return _buildChatBubble(context, msg);
              },
            ),
          ),
          _buildInputArea(context),
        ],
      ),
    );
  }

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
                  controller: textController,
                  decoration: const InputDecoration(
                    hintText: "Nachricht...",
                    border: InputBorder.none,
                    isDense: true,
                    contentPadding: EdgeInsets.symmetric(horizontal: 4, vertical: 8),
                  ),
                  onSubmitted: (_) => onSendPressed(),
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
                onPressed: onSendPressed,
              ),
            ],
          ),
        ),
      ),
    );
  }
}