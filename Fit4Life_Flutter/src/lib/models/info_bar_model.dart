import 'package:flutter/material.dart';

void showInfoBar(
  BuildContext context,
  String message, {
  Duration duration = const Duration(seconds: 2),
}) {
  final messenger = ScaffoldMessenger.maybeOf(context);
  if (messenger == null) return;

  messenger.showSnackBar(
    SnackBar(
      backgroundColor: Theme.of(context).colorScheme.primary,
      content: Text(
        message,
        style: TextStyle(
          color: Theme.of(context).colorScheme.onPrimary,
          fontSize: 14,
        ),
      ),
      duration: duration,
    ),
  );
}
