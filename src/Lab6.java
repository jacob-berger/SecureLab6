import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Lab6 {

	private static PrintStream errorOutputStream;


	public static void main(String[] args) {

		File file = new File("errors-java.txt");
		try {
			errorOutputStream = new PrintStream(file);
			System.setErr(errorOutputStream);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		Scanner kb = new Scanner(System.in);

		boolean validName = false;

		do {
			System.out.println("Enter LASTNAME:");
			String lastName = kb.nextLine();
			if (validateName(lastName)) {

				System.out.println("Enter FIRSTNAME:");
				String firstName = kb.nextLine();
				if (validateName(firstName)) {
					validName = true;
				}
			}

		} while (!validName);

	}

	private static boolean validateName(String input) {
		if (input == null || input.length() < 1) {
			System.err.println("Name was null or empty.");
			return false;
		}
		if (input.length() > 50) {
			System.err.println("Name was too long.");
			return false;
		}
		Pattern pattern = Pattern.compile("^[A-Za-z]+(\\s[A-Za-z]*)*$");
		Matcher matcher = pattern.matcher(input);
		boolean matched = matcher.matches();
		if (!matched) {
			System.out.println("Entered name is invalid.");
			System.err.println("Entered name is invalid.");
		}

		return matched;
	}

}
