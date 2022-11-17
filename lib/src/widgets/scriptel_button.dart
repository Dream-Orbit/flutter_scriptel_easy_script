import 'package:easyscript/src/types/constants.dart';
import 'package:flutter/material.dart';

class ScriptelButton extends StatelessWidget {
  final void Function() onTap;
  final String label;

  const ScriptelButton({Key? key, required this.onTap, required this.label})
      : super(key: key);

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: onTap,
      child: Container(
        padding: const EdgeInsets.symmetric(horizontal: 10, vertical: 5),
        decoration: BoxDecoration(
          border: Border.all(
            color: primaryColor,
            width: 1.5,
          ),
        ),
        child: Text(label,
            style: const TextStyle(
                color: primaryColor, fontWeight: FontWeight.bold)),
      ),
    );
  }
}
