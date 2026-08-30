import 'package:flutter/material.dart';

class SearchDialog<T> extends StatefulWidget {
  const SearchDialog({
    super.key,
    required this.title,
    required this.items,
    required this.itemBuilder,
    required this.searchDelegate,
    this.onItemSelected,
  });

  final String title;
  final List<T> items;
  final Widget Function(BuildContext, T, VoidCallback) itemBuilder;
  final List<T> Function(String query, List<T> items) searchDelegate;
  final Function(T)? onItemSelected;

  @override
  State<SearchDialog<T>> createState() => _SearchDialogState<T>();
}

class _SearchDialogState<T> extends State<SearchDialog<T>> {
  late TextEditingController _searchController;
  late List<T> _filteredItems;

  @override
  void initState() {
    super.initState();
    _searchController = TextEditingController();
    _filteredItems = widget.items;
  }

  @override
  void dispose() {
    _searchController.dispose();
    super.dispose();
  }

  void _updateSearch(String query) {
    setState(() {
      _filteredItems = widget.searchDelegate(query, widget.items);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Dialog(
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(30),
      ),
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            // Header
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Expanded(
                  child: Text(
                    widget.title,
                    style: Theme.of(context).textTheme.headlineSmall?.copyWith(
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
                IconButton(
                  icon: const Icon(Icons.close, size: 30),
                  onPressed: () => Navigator.pop(context),
                  padding: EdgeInsets.zero,
                  constraints: const BoxConstraints(),
                ),
              ],
            ),
            const SizedBox(height: 16),
            // Search
            TextField(
              controller: _searchController,
              onChanged: _updateSearch,
              decoration: InputDecoration(
                hintText: 'Suchen',
                prefixIcon: Icon(Icons.search, color: Theme.of(context).colorScheme.primary),
                border: OutlineInputBorder(
                  borderRadius: BorderRadius.circular(20),
                ),
                contentPadding: const EdgeInsets.symmetric(
                  horizontal: 12,
                  vertical: 10,
                ),
              ),
            ),
            const SizedBox(height: 16),
            // Items
            ConstrainedBox(
              constraints: const BoxConstraints(
                maxHeight: 400,
              ),
              child: _filteredItems.isEmpty
                  ? Center(
                      child: Padding(
                        padding: const EdgeInsets.all(16.0),
                        child: Text(
                          'Keine Ergebnisse gefunden',
                          style: Theme.of(context).textTheme.bodyLarge,
                        ),
                      ),
                    )
                  : ListView.separated(
                      shrinkWrap: true,
                      itemCount: _filteredItems.length,
                      separatorBuilder: (_, _) => const Divider(height: 1),
                      itemBuilder: (context, index) {
                        final item = _filteredItems[index];
                        return widget.itemBuilder(
                          context,
                          item,
                          () {
                            widget.onItemSelected?.call(item);
                            Navigator.pop(context, item);
                          },
                        );
                      },
                    ),
            ),
          ],
        ),
      ),
    );
  }
}
