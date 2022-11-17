class InvalidCharacterException extends Error {
  final String character;

  InvalidCharacterException({required this.character});

  @override
  String toString() {
    return "Invalid keyboard code detected in compression stream C=$character";
  }
}
