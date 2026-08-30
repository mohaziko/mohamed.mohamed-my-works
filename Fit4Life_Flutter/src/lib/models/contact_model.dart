enum ChatType {single, group}

class ContactData {
  final String username;
  final DateTime lastMessageTime;
  final bool isOnline;
  final ChatType type;
  final List<String> members;
  final bool isPrivate;
  final int score;

  ContactData({
    required this.username,
    required this.lastMessageTime,
    this.isOnline = false,
    this.type = ChatType.single,
    this.members = const[],
    this.isPrivate = true,
    this.score = 0,
  });

  Map<String, dynamic> toMap() {
    return {
      'username': username,
      'lastMessageTime': lastMessageTime.millisecondsSinceEpoch,
      'isOnline': isOnline,
      'type': type.index,
      'members': members,
      'isPrivate': isPrivate,
      'score': score,
    };
  }

  factory ContactData.fromMap(Map<dynamic, dynamic> map) {
    return ContactData(
      username: map['username'] as String,
      lastMessageTime: DateTime.fromMillisecondsSinceEpoch(map['lastMessageTime'] as int),
      isOnline: map['isOnline'] as bool? ?? false,
      type: ChatType.values[map['type'] as int? ?? 0],
      members: (map['members'] as List<dynamic>?)?.cast<String>() ?? [],
      isPrivate: map['isPrivate'] as bool? ?? true,
      score: map['score'] as int? ?? 0,
    );
  }
}