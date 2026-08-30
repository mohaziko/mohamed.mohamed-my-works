class ChatMessage {
  final String text;
  final DateTime time;
  final bool isMe; 

  ChatMessage({
    required this.text,
    required this.time,
    required this.isMe,
  });

  Map<String, dynamic> toMap() {
    return {
      'text': text,
      'time': time.millisecondsSinceEpoch, 
      'isMe': isMe,
    };
  }

  factory ChatMessage.fromMap(Map<dynamic, dynamic> map) {
    return ChatMessage(
      text: map['text'] as String,
      time: DateTime.fromMillisecondsSinceEpoch(map['time'] as int),
      isMe: map['isMe'] as bool,
    );
  }
}