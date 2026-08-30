import '../models/contact_model.dart';
import '../models/chat_model.dart'; 
import 'crudtemplate.dart';

class SocialCrud extends Crud {
  SocialCrud() : super(dbName: 'social_box');

  List<ContactData> getPotentialUsers() {
    final now = DateTime.now();
    
    return [
      ContactData(username: "@lauraweber", score: 2450, lastMessageTime: now, isOnline: true),
      ContactData(username: "@timbergmann", score: 1890, lastMessageTime: now),
      ContactData(username: "@daniels", score: 3120, lastMessageTime: now),
      ContactData(username: "@sophiefit", score: 1200, lastMessageTime: now, isOnline: true),
      ContactData(username: "@chrisgym", score: 2800, lastMessageTime: now),
      ContactData(username: "@annayoga", score: 1650, lastMessageTime: now),
      ContactData(username: "@maxpower", score: 4500, lastMessageTime: now, isOnline: true),
      ContactData(username: "@lisarun", score: 2100, lastMessageTime: now),
      ContactData(username: "@kevink", score: 950, lastMessageTime: now),
      ContactData(username: "@sarahschmidt", score: 3200, lastMessageTime: now),
      ContactData(username: "@tommueller", score: 1450, lastMessageTime: now),
      ContactData(username: "@juliab", score: 2750, lastMessageTime: now),
      ContactData(username: "@mehmetyilmaz", score: 1980, lastMessageTime: now),
      ContactData(username: "@elenak", score: 2300, lastMessageTime: now, isOnline: true),
      ContactData(username: "@fabiansport", score: 1100, lastMessageTime: now),
      ContactData(username: "@vanessap", score: 1750, lastMessageTime: now),
      ContactData(username: "@janrunner", score: 2900, lastMessageTime: now),
      ContactData(username: "@leapilates", score: 1350, lastMessageTime: now),
      ContactData(username: "@denniscrossfit", score: 3600, lastMessageTime: now, isOnline: true),
      ContactData(username: "@ninaactive", score: 2050, lastMessageTime: now),
    ];
  }

  Future<List<ContactData>> getContacts() async {
    final box = await dbBox;
    if (box.isEmpty) return [];

    return box.values.map((item) {
      if (item is! Map) return null;
      try {
        final mapItem = Map<String, dynamic>.from(item);
        if (mapItem.containsKey('username') && !mapItem.containsKey('text')) {
           return ContactData.fromMap(mapItem);
        }
        return null;
      } catch (e) { return null; }
    }).whereType<ContactData>().toList();
  }

  Future<void> saveContact(ContactData contact) async {
    await saveToDB(contact.username, contact.toMap());
  }

  Future<void> updateContactTime(String username, DateTime newTime) async {
    final box = await dbBox;
    
    final contactMap = box.get(username);
    
    if (contactMap != null) {
      final contact = ContactData.fromMap(Map<String, dynamic>.from(contactMap));
      
      final updatedContact = ContactData(
        username: contact.username,
        isOnline: contact.isOnline,
        lastMessageTime: newTime, 
        score: contact.score,     
        type: contact.type,
        members: contact.members,
        isPrivate: contact.isPrivate,
      );

      await saveContact(updatedContact);
    }
  }

  Future<void> saveChatHistory(String contactName, List<ChatMessage> messages) async {
    final dbKey = "chat_$contactName";
    final messagesAsMaps = messages.map((m) => m.toMap()).toList();
    await saveToDB(dbKey, messagesAsMaps);
  }

  Future<List<ChatMessage>> getChatHistory(String contactName) async {
    final box = await dbBox;
    final dbKey = "chat_$contactName";

    if (!box.containsKey(dbKey)) {
      return []; 
    }

    final rawList = box.get(dbKey) as List;

    return rawList.map((item) {
      return ChatMessage.fromMap(Map<dynamic, dynamic>.from(item));
    }).toList();
  }
}