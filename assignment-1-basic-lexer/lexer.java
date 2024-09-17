import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

class Lexer {
    public static class DFA {
        List<String> RESERVED_WORDS = Arrays.asList("TAGS", "BEGIN", "SEQUENCE", "INTEGER", "DATE", "END");
        List<Integer> WHITESPACES = Arrays.asList(9, 10, 11, 12, 13, 32);
        List<Integer> SPECIALS = Arrays.asList((int) '"', (int) '|', (int) '(', (int) ')', (int) ',', (int) '{',
                (int) '}');
        List<Integer> NUMBERS = Arrays.asList(48, 49, 50, 51, 52, 53, 54, 55, 56, 57);

        List<Integer> UPPER_AZ = new ArrayList<>();
        List<Integer> LOWER_AZ = new ArrayList<>();

        enum State {
            WhiteSpace,

            TypeRef1,
            TypeRef2,

            Identifier1,
            Identifier2,

            Number1,
            Number2,

            Assign1,
            Assign2,
            Assign3,

            Range1,
            Range2,

            Special
        }

        State startState;
        Set<State> finalStates = new HashSet<>();
        Map<String, State> transitions = new HashMap<>();

        public DFA() {
            initAlphabets();
            drawPartialDFA();
        }

        private void initAlphabets() {
            // a..z
            for (int i = 97; i <= 122; i++) {
                LOWER_AZ.add(i);
            }
            // A..Z
            for (int i = 65; i <= 90; i++) {
                UPPER_AZ.add(i);
            }
        }

        public String encodeTransition(State state, int characterInt) {
            return state.name() + " " + Integer.toString(characterInt);
        }

        public void drawPartialDFA() {
            // === 1. init states ===

            startState = State.WhiteSpace;

            finalStates.add(State.WhiteSpace);
            finalStates.add(State.TypeRef1);
            finalStates.add(State.Identifier1);
            finalStates.add(State.Number1);
            finalStates.add(State.Number2);
            finalStates.add(State.Assign3);
            finalStates.add(State.Range2);
            finalStates.add(State.Special);

            // === 2. init transitions ===

            drawMultiple(State.WhiteSpace, State.WhiteSpace, WHITESPACES);

            drawMultiple(State.WhiteSpace, State.TypeRef1, UPPER_AZ);
            drawMultiple(State.TypeRef1, State.TypeRef1, LOWER_AZ);
            drawMultiple(State.TypeRef1, State.TypeRef1, UPPER_AZ);
            drawMultiple(State.TypeRef1, State.TypeRef1, NUMBERS);
            drawMultiple(State.TypeRef1, State.WhiteSpace, WHITESPACES); // Final
            drawSingle(State.TypeRef1, State.TypeRef2, (int) '-');
            drawMultiple(State.TypeRef2, State.TypeRef1, LOWER_AZ);
            drawMultiple(State.TypeRef2, State.TypeRef1, UPPER_AZ);
            drawMultiple(State.TypeRef2, State.TypeRef1, NUMBERS);

            drawMultiple(State.WhiteSpace, State.Identifier1, LOWER_AZ);
            drawMultiple(State.Identifier1, State.Identifier1, LOWER_AZ);
            drawMultiple(State.Identifier1, State.Identifier1, UPPER_AZ);
            drawMultiple(State.Identifier1, State.Identifier1, NUMBERS);
            drawMultiple(State.Identifier1, State.WhiteSpace, WHITESPACES); // Final
            drawSingle(State.Identifier1, State.Identifier2, (int) '-');
            drawMultiple(State.Identifier2, State.Identifier1, LOWER_AZ);
            drawMultiple(State.Identifier2, State.Identifier1, UPPER_AZ);
            drawMultiple(State.Identifier2, State.Identifier1, NUMBERS);

            drawSingle(State.WhiteSpace, State.Number1, (int) '0');
            drawMultiple(State.Number1, State.WhiteSpace, WHITESPACES); // Final

            drawMultiple(State.WhiteSpace, State.Number2, NUMBERS.subList(1, NUMBERS.size())); // 1 .. 9
            drawMultiple(State.Number2, State.Number2, NUMBERS);
            drawMultiple(State.Number2, State.WhiteSpace, WHITESPACES); // Final

            drawSingle(State.WhiteSpace, State.Assign1, (int) ':');
            drawSingle(State.Assign1, State.Assign2, (int) ':');
            drawSingle(State.Assign2, State.Assign3, (int) '=');
            drawMultiple(State.Assign3, State.WhiteSpace, WHITESPACES); // Final

            drawSingle(State.WhiteSpace, State.Range1, (int) '.');
            drawSingle(State.Range1, State.Range2, (int) '.');
            drawMultiple(State.Range2, State.WhiteSpace, WHITESPACES); // Final

            drawMultiple(State.WhiteSpace, State.Special, SPECIALS);
            drawMultiple(State.Special, State.WhiteSpace, WHITESPACES); // Final
        }

        public void drawSingle(State start, State end, int characterInt) {
            transitions.put(encodeTransition(start, characterInt), end);
        }

        public void drawMultiple(State start, State end, List<Integer> characters) {
            for (int character : characters) {
                transitions.put(encodeTransition(start, character), end);
            }
        }

        public boolean accepts(String input) {
            State currentState = startState;

            for (int i = 0; i < input.length(); i++) {
                char character = input.charAt(i);

                // DEBUG
                System.out.println(i + "-->" + (int) character + "-->" + character);
                System.out.println("Before: " + currentState.name());

                // Escape right away if character is invalid => So our DFA model is not complete
                // but PARTIAL
                if (!transitions.containsKey(encodeTransition(currentState, character))) {
                    // DEBUG
                    System.out.println(i + "-->" + (int) character + "-->" + character);
                    System.out.println(currentState.name());
                    System.out.println("Invalid");
                    System.out.println();

                    return false;
                }

                currentState = transitions.get(encodeTransition(currentState, character));

                // DEBUG
                System.out.println("After: " + currentState.name());
                System.out.println();
            }

            // DEBUG
            System.out.println(currentState.name());
            if (finalStates.contains(currentState)) {
                System.out.println("Not Successful");
            }
            System.out.println();

            return finalStates.contains(currentState);
        }
    }

    public static String readInputFile(String path) throws IOException {
        Path filePath = Paths.get(path);

        try {
            String content = Files.readString(filePath);
            return content;
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
            return null;
        }
    }

    public static void main(String[] args) throws IOException {
        // 1. Read input
        String input = readInputFile(args[0]);

        // DEBUG
        // System.out.println(input);

        // 2. Create DFA
        DFA dfa = new DFA();
        System.out.println("Result: " + dfa.accepts(input));
    }
}