import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:src/dialogs/search_dialog.dart';

class FoodSearchDialog extends StatefulWidget {
  const FoodSearchDialog({
    super.key,
    required this.onFoodSelected,
    required this.foods,
  });

  final Function(String name, int calories, double fats, double protein) onFoodSelected;
  final List<Map<String, dynamic>> foods;

  @override
  State<FoodSearchDialog> createState() => _FoodSearchDialogState();
}

class _FoodSearchDialogState extends State<FoodSearchDialog> {
  @override
  Widget build(BuildContext context) {
    return Material(
      type: MaterialType.transparency,
      child: Center(
        child: SearchDialog<Map<String, dynamic>>(
          title: 'Lebensmittel wählen',
          items: widget.foods,
          searchDelegate: (query, items) {
            if (query.isEmpty) return items;
            final lower = query.toLowerCase();
            return items
                .where((item) => item['name']
                    .toString()
                    .toLowerCase()
                    .contains(lower))
                .toList();
          },
          itemBuilder: (context, item, onSelect) {
            return InkWell(
              onTap: () {
                HapticFeedback.selectionClick();
                onSelect();
              },
              child: Padding(
                padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 12),
                child: Row(
                  children: [
                    Expanded(
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text(
                            item['name'],
                            style: Theme.of(context).textTheme.bodyLarge?.copyWith(
                                  fontWeight: FontWeight.w600,
                                ),
                          ),
                          const SizedBox(height: 4),
                          Text(
                            '${item['calories']} kcal · ${item['fats']}g F · ${item['protein']}g P',
                            style: Theme.of(context).textTheme.bodyMedium?.copyWith(
                                  color: Colors.grey[600],
                                ),
                          ),
                        ],
                      ),
                    ),
                  ],
                ),
              ),
            );
          },
          onItemSelected: (item) => widget.onFoodSelected(
            item['name'],
            item['calories'],
            item['fats'],
            item['protein'],
          ),
        ),
      ),
    );
  }
}
