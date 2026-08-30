import 'package:flutter/material.dart';

class TrainingCheckboxTile extends StatefulWidget {
  const TrainingCheckboxTile({
    super.key,
    required this.value,
    required this.onChanged,
    required this.title,
  });

  final bool value;
  final ValueChanged<bool?> onChanged;
  final String title;

  @override
  State<TrainingCheckboxTile> createState() => _TrainingCheckboxTileState();
}

class _TrainingCheckboxTileState extends State<TrainingCheckboxTile> {
  @override
  Widget build(BuildContext context) {
    return CheckboxListTile(
      value: widget.value,
      onChanged: widget.onChanged,
      title: Text(
        widget.title,
        style: const TextStyle(fontWeight: FontWeight.w500),
      ),
      controlAffinity: ListTileControlAffinity.leading,
      contentPadding: EdgeInsets.zero,
    );
  }
}
