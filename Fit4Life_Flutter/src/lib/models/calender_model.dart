import 'package:flutter/material.dart';
import 'package:scrolling_buttons_bar/scrolling_buttons_bar.dart';

class CalenderModel extends StatefulWidget {
  const CalenderModel({
    super.key, 
    this.onDateSelected, 
    this.daysInPast = 7, 
    this.daysInFuture = 2
  });

  final int daysInPast;
  final int daysInFuture;
  final ValueChanged<DateTime>? onDateSelected;

  @override
  State<CalenderModel> createState() => _CalenderModelState();
}

class _CalenderModelState extends State<CalenderModel> {
  late int selectedItemIndex;
  late DateTime selectedDate;

  final ScrollController _scrollController = ScrollController();

  // WICHTIG: Entfernt Uhrzeit (setzt auf 00:00:00)
  DateTime _stripTime(DateTime date) {
    return DateTime(date.year, date.month, date.day);
  }

  @override
  void initState() {
    super.initState();
    // Startwert setzen: Heute (ohne Uhrzeit)
    selectedItemIndex = widget.daysInPast;
    selectedDate = _stripTime(DateTime.now());

    WidgetsBinding.instance.addPostFrameCallback((_) {
      if (mounted) {
        widget.onDateSelected?.call(selectedDate);
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    double childHeight = MediaQuery.of(context).size.height / 12;
    double childWidth = MediaQuery.of(context).size.width / 5;
    int totalDays = widget.daysInPast + widget.daysInFuture + 1;
    
    // Basis ist Heute 00:00 Uhr
    DateTime baseDate = _stripTime(DateTime.now());

    return Column(
      mainAxisSize: MainAxisSize.min,
      children: [
        ScrollingButtonBar(
          selectedItemIndex: selectedItemIndex,
          scrollController: _scrollController,
          childWidth: childWidth,
          childHeight: childHeight,
          foregroundColor: Colors.grey[300]!,
          curve: Curves.easeInOut,
          radius: 15,
          children: buildDateItems(baseDate, totalDays)
        ),
        Container(height: 5, color: Theme.of(context).colorScheme.primary)
      ],
    );
  }

  List<ButtonsItem> buildDateItems(DateTime baseDate, int amount) {
    List<String> weekdays = ["Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"];
    List<String> months = [
      "Jan", "Feb", "Mär", "Apr", "Mai", "Jun",
      "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"
    ];
    
    // Wir rechnen direkt mit year/month/day um DST-Probleme zu umgehen
    DateTime startDate = DateTime(baseDate.year, baseDate.month, baseDate.day - widget.daysInPast);
    
    List<ButtonsItem> items = [];
    
    for (int i = 0; i < amount; i++) {
      // Loop: Startdatum + i Tage
      DateTime currentDate = DateTime(startDate.year, startDate.month, startDate.day + i);
      
      bool isToday = currentDate.year == baseDate.year &&
                     currentDate.month == baseDate.month &&
                     currentDate.day == baseDate.day;
      
      items.add(
        ButtonsItem(
          child: InkWell(
            onTap: () {
               setState(() {
                 selectedItemIndex = i;
                 selectedDate = currentDate;
               });
               widget.onDateSelected?.call(currentDate);
            },
            child: Row(
              mainAxisSize: MainAxisSize.min,
              children: [
                if (i == 0) Container(
                  width: 1,
                  height: 50,
                  color: Theme.of(context).colorScheme.primary,
                ),
                Expanded(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      Text(
                        // Korrekte Wochentagsanzeige (Mo=0 .. So=6)
                        weekdays[(currentDate.weekday - 1) % 7],
                        style: TextStyle(
                          fontSize: isToday ? 13 : 10,
                          fontWeight: isToday ? FontWeight.bold : FontWeight.normal,
                          color: isToday ? Theme.of(context).colorScheme.primary : Colors.grey[600],
                        ),
                      ),
                      const SizedBox(height: 2),
                      Text(
                        currentDate.day.toString(),
                        style: TextStyle(
                          fontSize: isToday ? 24 : 18,
                          fontWeight: FontWeight.bold,
                          color: isToday ? Theme.of(context).colorScheme.primary : null,
                        ),
                      ),
                      const SizedBox(height: 1),
                      Text(
                        months[(currentDate.month - 1) % 12],
                        style: TextStyle(
                          fontSize: isToday ? 13 : 10,
                          fontWeight: isToday ? FontWeight.bold : FontWeight.normal,
                          color: isToday ? Theme.of(context).colorScheme.primary : Colors.grey[600],
                        ),
                      ),
                    ],
                  ),
                ),
                Container(
                  width: 1,
                  height: 50,
                  color: Theme.of(context).colorScheme.primary,
                ),
              ],
            ),
          ),
          onTap: () {
            setState(() {
              selectedItemIndex = i;
              selectedDate = currentDate;
            });
            widget.onDateSelected?.call(currentDate);
          },
        ),
      );
    }
    return items;
  }
}