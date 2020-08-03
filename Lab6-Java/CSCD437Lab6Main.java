// Daniel Tekle
// Jacob Berger

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Arrays;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import java.security.MessageDigest;
import java.util.Arrays;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.spec.IvParameterSpec;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class CSCD437Lab6Main {

	private static PrintStream errorOutputStream, outputPrintStream;
	private static String lastName, firstName, inFilename, outFilename;
	private static int first, second;
	private static String key = "asdf;lkjqwerpoiu";


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
			System.out.println("Enter first name: ");
			firstName = kb.nextLine();
			if (validateString(firstName, "name")) {

				System.out.println("Enter last name: ");
				lastName = kb.nextLine();
				validName = validateString(lastName, "name");
			}

		} while (!validName);

		boolean validInt = false;
		do {
			System.out.println("Enter first int: ");
			try {
				first = Integer.parseInt(kb.nextLine());
				System.out.println("Enter second int: ");
				second = Integer.parseInt(kb.nextLine());
				validInt = true;
			} catch (NumberFormatException e) {
				System.out.println("Integer is invalid.");
				System.err.println("Integer is invalid.");
			}
		} while (!validInt);

		boolean validFileName = false;
		do {
			System.out.println("Enter input filename: ");
			inFilename = kb.nextLine();
			validFileName = validateString(inFilename, "filename");
		} while (!validFileName);

		validFileName = false;
		do {
			System.out.println("Enter output filename: ");
			outFilename = kb.nextLine();
			validFileName = validateString(outFilename, "filename");
		} while (!validFileName);

		boolean validPassword = false;
		do {
			System.out.println("Enter a password (10-15 characters): ");
			String password = kb.nextLine();
			validPassword = validateString(password, "password");

			if (validPassword) {
//				String salt = BCrypt.gensalt();
//				BCrypt.hashpw(password, salt);
				File passwordFile = new File("passwords.txt");
				try {
					PrintStream printStream = new PrintStream(passwordFile);
//					printStream.println(BCrypt.hashpw(password, salt));
					printStream.println(encrypt(password, key));
				} catch (IOException e) {
					System.out.println("Could not create password file.");
					System.err.println("Could not create password file.");
				} catch (Exception exception) {
					exception.printStackTrace();
				}
				System.out.println("Retype password: ");
				String retype = kb.nextLine();
				validPassword = validateString(retype, "password");
				String hashedPassword = "";
				String hashedRetype = "";
				if (validPassword) {
					try {
						Scanner scanner = new Scanner(passwordFile);
						hashedPassword = scanner.nextLine();
						scanner.close();
						hashedRetype = decrypt(retype.getBytes(), key);
					} catch (FileNotFoundException e) {
						System.out.println("Could not find passwords.txt");
					} catch (Exception exception) {
						exception.printStackTrace();
					}
//					if (BCrypt.checkpw(retype, hashedPassword)) {
//						System.out.println("Passwords matched.");
					if (hashedPassword.compareTo(hashedRetype) == 0) {
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
			System.out.println("Could not find input file.");
			System.err.println("Could not find input file.");
//			System.out.println(e.getCause());
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
				pattern = Pattern.compile("^[\\p{Alnum}\\p{Punct}\\s]{10,15}$");
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

	public static byte[] encrypt(String plain, String encryptionKey) throws Exception {

		String IV = "QWERASDFUIOPJKL;";

		Cipher cipher = Cipher.getInstance("AES/CBC/NoPadding", "SunJCE");
		SecretKeySpec key = new SecretKeySpec(encryptionKey.getBytes("UTF-8"), "AES");
		cipher.init(Cipher.ENCRYPT_MODE, key,new IvParameterSpec(IV.getBytes("UTF-8")));
		return cipher.doFinal(plain.getBytes("UTF-8"));
	}

	public static String decrypt(byte[] cipherText, String encryptionKey) throws Exception{

		String IV = "QWERASDFUIOPJKL;";

		Cipher cipher = Cipher.getInstance("AES/CBC/NoPadding", "SunJCE");
		SecretKeySpec key = new SecretKeySpec(encryptionKey.getBytes("UTF-8"), "AES");
		cipher.init(Cipher.DECRYPT_MODE, key,new IvParameterSpec(IV.getBytes("UTF-8")));
		return new String(cipher.doFinal(cipherText),"UTF-8");
	}

}
