import 'package:flutter/material.dart';


class CardContainerConstants {
    static const double containerPadding = 20.0;
    static const double containerBorderRadius = 12.0;
}

class CardContainerModel extends StatelessWidget {
  const CardContainerModel({super.key, required this.context, required this.child, this.padding = 0.0});

  final BuildContext context;
  final Widget child;
  final double padding;

  @override
  Widget build(BuildContext context) {
    return Container(
      width: double.infinity,
      padding: EdgeInsets.all(CardContainerConstants.containerPadding),
      decoration: BoxDecoration(
        color: Colors.grey[300],
        borderRadius: BorderRadius.circular(CardContainerConstants.containerBorderRadius),
      ),
      child: Padding(
        padding: EdgeInsets.all(padding),
        child: child,
      ),
    );
  }
}