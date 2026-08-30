import 'package:flutter/material.dart';
import 'package:src/dialogs/search_dialog.dart';
import 'package:src/data/training_data.dart';


class TrainingSearchDialog extends StatefulWidget {
  const TrainingSearchDialog({
    super.key,
    required this.onPlanSelected,
    required this.trainingPlans,
    this.currentPlan,
  });

  final Function(TrainingPlan) onPlanSelected;
  final List<TrainingPlan> trainingPlans;
  final TrainingPlan? currentPlan;

  @override
  State<TrainingSearchDialog> createState() => _TrainingSearchDialogState();
}

class _TrainingSearchDialogState extends State<TrainingSearchDialog> {
  int? _difficultyFilter; // null = Alle

  List<TrainingPlan> get _filteredPlans {
    if (_difficultyFilter == null) return widget.trainingPlans;
    return widget.trainingPlans
        .where((p) => p.difficulty == _difficultyFilter)
        .toList();
  }

  @override
  Widget build(BuildContext context) {
    return Material(
      type: MaterialType.transparency,
      child: Center(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            LayoutBuilder(
              builder: (context, constraints) {
                return Wrap(
                  crossAxisAlignment: WrapCrossAlignment.center,
                  spacing: 12,
                  children: [
                    _difficultyChip(context, label: 'Alle', value: null),
                    _difficultyChip(context, label: '1 ★', value: 1),
                    _difficultyChip(context, label: '2 ★', value: 2),
                    _difficultyChip(context, label: '3 ★', value: 3),
                  ],
                );
              },
            ),
            // Suche + Liste
            Transform.translate(
              offset: const Offset(0, -15),
              child: SearchDialog<TrainingPlan>(
              key: ValueKey(_difficultyFilter),
              title: 'Trainingsplan wählen',
              items: _filteredPlans,
              searchDelegate: (query, items) {
                if (query.isEmpty) return items;
                return items
                    .where((plan) =>
                        plan.name.toLowerCase().contains(query.toLowerCase()) ||
                        (plan.description?.toLowerCase().contains(query.toLowerCase()) ?? false))
                    .toList();
              },
              itemBuilder: (context, plan, onSelect) {
                final isCurrentPlan = widget.currentPlan?.name == plan.name;
                return InkWell(
                  onTap: onSelect,
                  child: Container(
                    decoration: BoxDecoration(
                      color: isCurrentPlan
                          ? Theme.of(context).colorScheme.primary.withAlpha(50)
                          : null,
                      borderRadius: BorderRadius.circular(8),
                    ),
                    child: Padding(
                      padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 12),
                      child: Row(
                        children: [
                          Expanded(
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              mainAxisSize: MainAxisSize.min,
                              children: [
                                Text(
                                  plan.name,
                                  style: Theme.of(context).textTheme.bodyLarge?.copyWith(
                                        fontWeight: isCurrentPlan ? FontWeight.bold : FontWeight.w500,
                                      ),
                                ),
                                if (plan.description != null) ...[
                                  const SizedBox(height: 4),
                                  Text(
                                    plan.description!,
                                    style: Theme.of(context).textTheme.bodySmall?.copyWith(
                                          color: Colors.grey[600],
                                        ),
                                  ),
                                ],
                              ],
                            ),
                          ),
                          const SizedBox(width: 12),
                          _buildStarRating(context, plan.difficulty)
                        ],
                      ),
                    ),
                  ),
                );
              },
              onItemSelected: widget.onPlanSelected,
              ),
            ),
         ],
        ),
      ),
    );
  }

  Widget _difficultyChip(BuildContext context, {required String label, required int? value}) {
    final bool selected = _difficultyFilter == value;
    return ChoiceChip(
      label: Text(label),
      selected: selected,
      onSelected: (_) {
        setState(() {
          _difficultyFilter = value;
        });
      },
    );
  }

  Widget _buildStarRating(BuildContext context, int difficulty, {double iconSize = 32}) {
    return Row(
      mainAxisSize: MainAxisSize.min,
      children: List.generate(3, (index) {
        return Icon(
          index < difficulty ? Icons.star : Icons.star_outline,
          color: Theme.of(context).colorScheme.primary,
          size: iconSize,
        );
      }),
    );
  }
}
