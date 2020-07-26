import java.io.*;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CSCD437Lab6Main {

	private static PrintStream errorOutputStream, inputPrintStream, outputPrintStream;
	private static String lastName, firstName, inFilename, outFilename, hashedPassword;
	private static int first, second;


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
			System.out.println("Enter last name:");
			lastName = kb.nextLine();
			if (validateName(lastName)) {

				System.out.println("Enter first name:");
				firstName = kb.nextLine();
				validName = validateName(firstName);
			}

		} while (!validName);

		boolean validInt = false;
		do {
			System.out.println("Enter first int:");
			try {
				first = Integer.parseInt(kb.nextLine());
				System.out.println("Enter second int:");
				second = Integer.parseInt(kb.nextLine());
				validInt = true;
			} catch (NumberFormatException e) {
				System.out.println("Integer is invalid.");
				System.err.println("Integer is invalid.");
			}
		} while (!validInt);

		boolean validFileName = false;
		do {
			System.out.println("Enter input filename:");
			inFilename = kb.nextLine();
			validFileName = validateFilename(inFilename);
		} while (!validFileName);

//		boolean validFileName = false;
		validFileName = false;
		do {
			System.out.println("Enter output filename:");
			outFilename = kb.nextLine();
			validFileName = validateFilename(outFilename);
		} while (!validFileName);

//		boolean validPassword = false;
//		do {
//			System.out.println("Enter a password:");
//			String password = kb.nextLine();
//			validPassword = validatePassword(password);
//
//			if (validPassword) {
//				System.out.println("TODO: PASSWORD");
//			}
//		} while (!validPassword);

		File output = new File(outFilename);
		try {
			outputPrintStream = new PrintStream(output);
			outputPrintStream.println(String.format("%s, %s", lastName, firstName));
			outputPrintStream.println(first + second);
			outputPrintStream.println(first * second);
			File input = new File(inFilename);
			Scanner inputFileReader = new Scanner(input);

			while (inputFileReader.hasNextLine()) {
				outputPrintStream.println(inputFileReader.nextLine());
			}
		} catch (FileNotFoundException e) {
			System.out.println("Could not create output file.");
			System.err.println("Could not create output file.");
		} catch (IOException e) {
			System.out.println("Could not read from input file.");
			System.err.println("Could not read from input file.");
		}

	}

	private static boolean validatePassword(String password) {

		Pattern pattern = Pattern.compile("^$");
		Matcher matcher = pattern.matcher(password);
		boolean matched = matcher.matches();

		return matched;

	}

	private static boolean validateFilename(String filename) {
		if (filename == null || filename.length() < 1) {
			System.err.println("Filename was null or empty.");
			System.out.println("Filename was null or empty.");
			return false;
		}
		if (filename.length() > 50) {
			System.err.println("Filename was too long.");
			System.out.println("Filename was too long.");
			return false;
		}

		Pattern pattern = Pattern.compile("^[\\p{Alnum}\\p{Punct}&&[^\\\\<>:\"/?|*]]+$");
		Matcher matcher = pattern.matcher(filename);
		boolean matched = matcher.matches();
		if (!matched) {
			System.err.println("Entered filename is invalid.");
			System.out.println("Entered filename is invalid.");
		}

		return matched;

	}

	private static boolean validateName(String input) {
		if (input == null || input.length() < 1) {
			System.err.println("Name was null or empty.");
			System.out.println("Name was null or empty.");
			return false;
		}
		if (input.length() > 50) {
			System.err.println("Name was too long.");
			System.out.println("Name was too long.");
			return false;
		}
		Pattern pattern = Pattern.compile("^[A-Za-z]+(\\s[A-Za-z]*)*$");
		Matcher matcher = pattern.matcher(input);
		boolean matched = matcher.matches();
		if (!matched) {
			System.err.println("Entered name is invalid.");
			System.out.println("Entered name is invalid.");
		}

		return matched;
	}

}
