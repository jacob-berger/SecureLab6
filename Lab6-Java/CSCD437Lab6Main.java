import java.io.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Arrays;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CSCD437Lab6Main {

	private static PrintStream errorOutputStream, outputPrintStream;
	private static String lastName, firstName, inFilename, outFilename;
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
			if (validateString(lastName, "name")) {

				System.out.println("Enter first name:");
				firstName = kb.nextLine();
				validName = validateString(firstName, "name");
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
			validFileName = validateString(inFilename, "filename");
		} while (!validFileName);

		validFileName = false;
		do {
			System.out.println("Enter output filename:");
			outFilename = kb.nextLine();
			validFileName = validateString(outFilename, "filename");
		} while (!validFileName);

		boolean validPassword = false;
		do {
			System.out.println("Enter a password:");
			String password = kb.nextLine();
			validPassword = validateString(password, "password");

			if (validPassword) {
				String salt = BCrypt.gensalt();
				BCrypt.hashpw(password, salt);
				File passwordFile = new File("passwords.txt");
				try {
					PrintStream printStream = new PrintStream(passwordFile);
					printStream.println(BCrypt.hashpw(password, salt));
				} catch (IOException e) {
					System.out.println("Could not create password file.");
					System.err.println("Could not create password file.");
				}
				System.out.println("Retype password:");
				String retype = kb.nextLine();
				validPassword = validateString(retype, "password");
				String hashedPassword = "";
				if (validPassword) {
					try {
						Scanner scanner = new Scanner(passwordFile);
						hashedPassword = scanner.nextLine();
						scanner.close();
					} catch (FileNotFoundException e) {
						System.out.println("Could not find passwords.txt");
					}
					if (BCrypt.checkpw(retype, hashedPassword)) {
						System.out.println("Passwords matched.");
					} else {
						System.out.println("Passwords did not match.");
						System.err.println("Passwords did not match.");
						validPassword = false;
					}
				}
			}
		} while (!validPassword);

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
			inputFileReader.close();
			outputPrintStream.close();
			errorOutputStream.close();
			kb.close();
		} catch (FileNotFoundException e) {
			System.out.println("Could not create output file.");
			System.err.println("Could not create output file.");
		}

	}

	private static boolean validateString(String input, String type) {

		if (input == null || input.length() < 1) {
			System.err.println(type + " was null or empty.");
			System.out.println(type + " was null or empty.");
			return false;
		}

		if (input.length() > 50) {
			System.err.println(type + " was too long.");
			System.out.println(type + " was too long.");
			return false;
		}

		Pattern pattern = null;
		switch (type) {
			case "filename":
				pattern = Pattern.compile("^[\\p{Alnum}\\p{Punct}&&[^\\\\<>:\"/?|*]]+$");
				break;
			case "password":
				pattern = Pattern.compile("^[\\p{Alnum}\\p{Punct}\\s]+$");
				break;
			case "name":
				pattern = Pattern.compile("^[A-Za-z]+(\\s[A-Za-z]*)*$");
				break;
			default:
				return false;
		}

		Matcher matcher = pattern.matcher(input);
		boolean matched = matcher.matches();
		if (!matched) {
			System.err.println("Entered input is invalid.");
			System.out.println("Entered input is invalid.");
		}

		return matched;

	}

}
