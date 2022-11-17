/*******************************************************************************
 * scriptel-easyscript.h - Copyright 2014 - Scriptel Corporation
 * ----
 * This header contains the definitions for all of the public structures and
 * functions for this library.
 ******************************************************************************/

/**
 * @mainpage Scriptel EasyScript Platform Independent C API
 * @section getting_started Getting Started
 * This library is designed to be integrated into your application to add
 * Scriptel EasyScript device functionality into your application. This library
 * supports Windows, Mac, and Linux.
 * The library package contains several directories:
 *  * src - Source code for the library
 *  * vs2017 - Visual Studio 2017 Project to use for Windows builds
 *  * example - Example using the library
 *  * doc - This documentation
 *
 * After building the library the only header you'll need is src/scriptel-easyscript.h.
 * This can be used in combination with the built DLL/Shared library in order to
 * add signature functionality to your application.
 *
 * @section building Building
 * In order to use this library you'll need to build it for the platform and
 * architecture you'd like to use it for.
 *
 * @subsection building_windows Building for Windows
 * You can build the Windows DLL by using the Visual Studio project contained
 * in the vs2010 directory. Open the project with Visual Studio and build the
 * solution.
 *
 * @subsection building_mac Building for Mac
 * You can build the dynamic library for Mac by using the Xcode command line
 * tools. Use the Makefile.osx in the root directory for this API.
 *
 * @subsection building_linux Building for Linux
 * You can build the dynamic library for Linux by using gcc and make. Use
 * Makefile.linux in the root of this API.
 */

//This set of defines is for the Visual C compiler to define exports/imports for
//the shared library.
#ifndef SCRIPTEL_EASYSCRIPT_H
#define SCRIPTEL_EASYSCRIPT_H

#ifdef _MSC_VER
	/**
     * This macro is used to abstract the way in which symbols are exported
     * for DLL's/Shared libraries. For Windows this symbol will always point
     * to a symbol export.
     */
	#define SCRIPTEL_SYMBOL_EXPORT __declspec(dllexport)
	//Check to see if we're producing or consuming the library.
	#ifdef SCRIPTEL_EXPORT_DLL
		/**
         * In this case the macro is being built on Windows and the
         * SCRIPTEL_EXPORT_DLL preprocessor directive is set which means that
         * the library is being built. This means that the symbol should be
         * exporting symbols.
         */
		#define SCRIPTEL_SYMBOL_LINKAGE __declspec(dllexport)
	#else
		/**
         * In this case the macro is being built on Windows and the
         * SCRIPTEL_EXPORT_DLL preprocessor directive is not set which means
         * that the library is being consumed. This means that the symbol
         * should be set to import symbols from the produced lib file.
         */
		#define SCRIPTEL_SYMBOL_LINKAGE __declspec(dllimport)
	#endif
#else
	/**
     * This symbol is used to abstract the way in which DLL/shared library
     * symbols are exported. This macro should always resolve to the call/keyword
     * used to export a symbol.
     *
     * For Linux/OSX this will always resolve to the extern keyword.
     */
	#define SCRIPTEL_SYMBOL_EXPORT extern
     /**
     * This symbol is used to abstract the way in which DLL/shared library
     * symbols are exported. This macro should always resolve to the call/keyword
     * used to produce or consume the shared library symbols. If the SCRIPTEL_EXPORT_DLL
     * preprocessor define is set it should resolve to export, otherwise import.
     *
     * For Linux/OSX this will always resolve to the extern keyword.
     */
	#define SCRIPTEL_SYMBOL_LINKAGE extern
#endif

#include <time.h>

/**
 * @brief This enumeration contains a set of return codes that functions in this
 * library may return.
 */
typedef enum {
    /**
     * This return code indicates that the last function called did not complete
     * successfully. Call scriptel_get_last_error() to get a more friendly
     * description of what failed.
     */
    SCRIPTEL_RETR_ERROR,
    /**
     * This return code indicates that the last function call completed
     * successfully.
     */
    SCRIPTEL_RETR_SUCCESS
} scriptel_return_status;

/**
 * @brief This enumeration contains a set of known financial card issuers.
 */
typedef enum {
    /**
     * American Express
     */
    AMERICAN_EXPRESS,
    /**
     * Diners Club
     */
    DINERS_CLUB,
    /**
     * Carte Blanche
     */
    CARTE_BLANCHE,
    /**
     * Discover
     */
    DISCOVER,
    /**
     * EnRoute
     */
    ENROUTE,
    /**
     * JCB
     */
    JCB,
    /**
     * Master Card
     */
    MASTERCARD,
    /**
     * Visa
     */
    VISA,
    /**
     * Unknown issuer.
     */
    UNKNOWN
} scriptel_financial_card_vendor;

/**
 * @brief This structure contains information about a signature protocol that can
 * be used to decode a signature buffer.
 */
typedef struct {
    /**
     * A textual name for the protocol.
     */
	const char* protocol_name;
    /**
     * A single character representing the start of stream.
     */
	char start_stream;
    /**
     * A single character representing the end of stream.
     */
	char end_stream;
	/**
	 * A single character representing that the signature has been cancelled.
	 */
	char cancel;
    /**
     * A single character representing pen up events or breaks between strokes.
     */
	char pen_up;
    /**
     * A set of characters representing a sentinel that appears immediately
     * after the start of stream character.
     */
	const char* sentinel;
    /**
     * The logical width of the protocol, used to maintain the aspect ratio of
     * the signature.
     */
	int width;
    /**
     * The logical height of the protocol, used to maintain the aspect ratio of
     * the signature.
     */
	int height;
    /**
     * The value table used to decode the signature.
     */
	const char value_table[2][2][23];
} scriptel_signature_protocol;

/**
 * @brief This structure contains information about a card swipe protocol that can be
 * used to decode a card swipe buffer.
 */
typedef struct {
    /**
     * Textual identifier for this protocol.
     */
	char* protocol_name;
    /**
     * A single character representing the start of the card swipe stream.
     */
	char start_stream;
    /**
     * A single character representing the end of the card swipe stream.
     */
	char end_stream;
    /**
     * A set of characters represnting a sentinel that appears immediately after
     * the start of stream character.
     */
	char* sentinel;
} scriptel_cardswipe_protocol;

/**
 * @brief This structure represents the first track of a financial card.
 */
typedef struct {
    /**
     * The account number on the card.
     */
	char* account_number;
    /**
     * The first name of the card holder.
     */
	char* first_name;
    /**
     * The last name of the card holder.
     */
	char* last_name;
    /**
     * The expiration date on the card. This is the last moment the card is
     * valid.
     */
	time_t expiration;
    /**
     * The service code on the card.
     */
	char* service_code;
    /**
     * Any other vendor specific data stored on the card.
     */
	char* discretionary_data;
} scriptel_financial_track_one;

/**
 * @brief This structure represents the second track of a financial card.
 */
typedef struct {
    /**
     * The account number on the card.
     */
	char* account_number;
    /**
     * The expiration date on the card. This is the last moment the card is
     * valid.
     */
	time_t expiration;
    /**
     * The service code on the card.
     */
	char* service_code;
    /**
     * Any other vendor specific data stored on the card.
     */
	char* discretionary_data;
} scriptel_financial_track_two;

/**
 * @brief This structure represents a financial card.
 */
typedef struct {
	scriptel_financial_track_one* track_one;		///< Track one of the financial card.
 	scriptel_financial_track_two* track_two;		///< Track two of the financial card.
	scriptel_financial_card_vendor card_issuer;		///< The issuer of the financial card.
	char number_valid;								///< Whether or not the card number is valid per Luhn's algorithm. 1 for valid, 0 for invalid.
} scriptel_financial_card;

/**
 * @brief This structure represents the first track of an identification card.
 */
typedef struct {
    /**
     * Two character state of residence of card holder.
     */
	char* state;
    /**
     * Cardholder's city of residence.
     */
	char* city;
    /**
     * Cardholder's last name.
     */
	char* last_name;
    /**
     * Cardholder's first name.
     */
	char* first_name;
    /**
     * Cardholder's middle name.
     */
	char* middle_name;
    /**
     * Cardholder's address.
     */
	char* address;
    /**
     * Discretionary data added by card issuer.
     */
	char* discretionary_data;
} scriptel_identification_track_one;

/**
 * @brief This structure represents track two of an identification card.
 */
typedef struct {
    /**
     * Issuer number.
     */
	char* issuer_number;
    /**
     * Document number.
     */
	char* id_number;
    /**
     * Date of expiration, the last moment this document is valid.
     */
	time_t expiration;
    /**
     * The birth date of the card holder.
     */
	time_t birth_date;
} scriptel_identification_track_two;

/**
 * @brief This structure represents track three of an identification card.
 */
typedef struct {
    /**
     * The CDS version of this card.
     */
	int cds_version;
    /**
     * The jurisidiction version of this card.
     */
	int jurisdiction_version;
    /**
     * The zip code of the card holder.
     */
	char* zip_code;
    /**
     * The license class of the card holder.
     */
	char* license_class;
    /**
     * Restrictions on the card holder.
     */
	char* restrictions;
    /**
     * Endorsements for the card holder.
     */
	char* endorsements;
    /**
     * Gender of the card holder.
     */
	char* sex;
    /**
     * Height of the card holder.
     */
	char* height;
    /**
     * Weight of the card holder.
     */
	char* weight;
    /**
     * Hair color of the card holder.
     */
	char* hair_color;
    /**
     * Eye color of the card holder.
     */
	char* eye_color;
} scriptel_identification_track_three;

/**
 * @brief This structure contains information from an identification card.
 */
typedef struct {
	scriptel_identification_track_one* track_one;		///< Track one of the identification card.
	scriptel_identification_track_two* track_two;		///< Track two of the identification card.
	scriptel_identification_track_three* track_three;	///< Track three of the identification card.
} scriptel_identification_card;

/**
* A set of constants indicating the type of data being sent to the application
*/
typedef enum {
	CBT_NEWSTROKE,			///< notification of a new stroke
	CBT_COORDINATE,			///< new new coordinate
	CBT_METADATA,			///< metadata for the upcoming signature
	CBT_CANCEL,				///< the signature has been cancelled
	CBT_END_OF_SIGNATURE,	///< the end of the signature has been reached succesfully
	CBT_CARD_DATA			///< card data
} callback_type;

/**
* @brief This structure represents a single coordinate.
*/
typedef struct {
	callback_type type;	///< this will be set to CBT_COORDINATE
	double x;					///< The horizontal coordinate, between 0 and protocol->width.
	double y;					///< The vertical coordinate, between 0 and protocol->height.
} scriptel_coordinate;

/**
* @brief This structure represents a data about the signature that will follow
*/
typedef struct {
	callback_type type;	///< this will be set to CBT_METADATA
	char *protocol_version;		///< a string comprising the protocol version info
	char *model;				///< a string comprising the signature pad model
	char *version;				///< a string comprising the firmware version
} signature_meta_data;

/**
 * @brief This structure represents a parsed card swipe.
 */
typedef struct {
	callback_type type;									///< this will be set to CBT_CARD_DATA
	char* protocol_version;								///< Protocol version that generated this card swipe.
	char* card_data;									///< Raw captured card data.
	scriptel_financial_card* financial_card;			///< Financial card information if the card was able to be parsed, null otherwise.
	scriptel_identification_card* identification_card;	///< Identification card information if the card was able to be parsed, null otherwise.
} scriptel_cardswipe;

/**
 *	Data being returned through a callback to the application
 */
typedef union {
	callback_type type;				///< the type of data contained
	signature_meta_data meta_data;	///< the meta data for the upcoming signature
	scriptel_coordinate	coordinate;	///< a signature coordinate
	scriptel_cardswipe card_swipe;	///< cardswipe information
} streaming_event_data;

/**
* @brief This structure represents a stroke which is made up of contingiously
* connected coordinates.
*/
typedef struct {
	/**
	* The number of coordinates in this stroke.
	*/
	int length;
	/**
	* The pointer to the first coordinate in this stroke.
	*/
	scriptel_coordinate* coordinates;
} scriptel_stroke;

/**
* @brief This structure represents a signature which is made up up the header
* information as well as zero or more strokes.
*/
typedef struct {
	char* protocol_version;		///< The protocol version used to encode/decode this signature.
	char* model;				///< The model number of the device used to make this signature.
	char* version;				///< The firmware version of the device used to make this firmware.
	int length;					///< The number of strokes in this signature.
	scriptel_stroke* strokes;	///< Pointer to the first stroke in the signature.
	int width;					///< Virtual width of the coordinate space (maximum x coordinate).
	int height;					///< Virtual height of the coordinate space (maximum y coordinate).
} scriptel_signature;

/**
 * @brief The standard signature protocol for the ScripTouch series devices.
 */
static const scriptel_signature_protocol STN_SIGNATURE_PROTOCOL = {
    "Standard EasyScript Protocol",
    '~',
    '`',
	'/',
    ' ',
    "STSIGN",
    240,
    64,
    {
        {
            {0x41,0x43,0x45,0x47,0x49,0x4b,0x4d,0x4f,0x51,0x53,0x55,0x57,0x59,0x21,0x23,0x25,0x26,0x28,0x2b,0x7d,0x22,0x3c,0x00},
            {0x42,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x5a,0x40,0x24,0x5e,0x2a,0x29,0x5f,0x7b,0x7c,0x3a,0x3e}
        }, {
            {0x61,0x63,0x65,0x67,0x69,0x6b,0x6d,0x6f,0x71,0x73,0x75,0x77,0x79,0x31,0x33,0x35,0x37,0x39,0x3d,0x5d,0x27,0x2c,0x00},
            {0x62,0x64,0x66,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x32,0x34,0x36,0x38,0x30,0x2d,0x5b,0x5c,0x3b,0x2e}
        }
    }
};



/**
 * @brief The standard card swipe protocol for the ScripTouch series devices.
 */
static const scriptel_cardswipe_protocol STN_CARDSWIPE_PROTOCOL = {
    "Standard EasyScript Card Swipe Protocol",
    '!',
    '\r',
    "STCARD"
};

/**
 * Maximum length of any error message.
 */
#define SCRIPTEL_ERROR_MAX_LEN 512


/**
 * The version number of this EasyScript library.
 * Please don't change this. It is used for support purposes.
 */
#define SCRIPTEL_EASYSCRIPT_LIBRARY_VERSION = "3.5.29";

/**
 * The date on which this library was produced.
 * Please don't change this. It is used for support purposes.
 */
#define SCRIPTEL_EASYSCRIPT_BUILD_DATE = "2022-08-30 17:12:23-0400";

/**
 * This function will attempt to parse a character buffer as a signature. You
 * are responsible for allocating the scriptel_signature structure as well as
 * freeing the memory when you're done. The contents of the structure can be
 * freed by calling scriptel_free_signature() after this function returns a
 * successful result.
 * @param sig_protocol Signature protocol to use.
 * @param signature Signature structure to fill in.
 * @param buffer Null terminated buffer to parse.
 * @param len Length of buffer, used for bounds checking. The lesser of len and the
 *        actual length of the null terminated buffer are used.
 * @return SCRIPTEL_RETR_SUCCESS on a successful result, SCRIPTEL_RETR_ERROR if
 * the function fails to parse the signature. If the signature fails to parse
 * the contents of the passed in structure should be treated as null.
 */
SCRIPTEL_SYMBOL_LINKAGE scriptel_return_status scriptel_keyboard_parse_signature(scriptel_signature_protocol* sig_protocol, scriptel_signature* signature, char* buffer, int len);

/**
 * This function will attempt to parse a character buffer as a card swipe. You
 * are responsible for allocating the scriptel_cardswipe structure as well as
 * freeing the memory when you're done. The contents of the structure can be
 * freed by calling scriptel_free_cardswipe() after this function returns a
 * successful result.
 * @param swipe_protocol Card swipe protocol to use.
 * @param swipe Card swipe structure to fill in.
 * @param buffer Buffer to parse.
 * @param len Length of buffer, used for bounds checking.
 * @return SCRIPTEL_RETR_SUCCESS on a successful result, SCRIPTEL_RETR_ERROR if
 * the function fails to parse the card swipe. If the card swipe fails to parse
 * the contents of the passed in structure should be treated as null.
 */
SCRIPTEL_SYMBOL_LINKAGE scriptel_return_status scriptel_keyboard_parse_cardswipe(const scriptel_cardswipe_protocol* swipe_protocol, scriptel_cardswipe* swipe, char* buffer, int len);

/**
 * This fuction allows you to stream in a set of characters and it
 * will attempt to decode signatures and card swipes as the characters are
 * passed in. To use this method be sure to implement your own EasyScriptEventListener
 * and pass it to ::scriptel_add_event_listener() prior to passing characters to this function.
 * This listener will be called when specific events are generated by decoding
 * the stream.
 * @param sig_protocol the protocol to use to interpret the data
 * @param chr Next character in the stream to parse
 */
SCRIPTEL_SYMBOL_LINKAGE scriptel_return_status scriptel_keyboard_parse_char(const scriptel_signature_protocol* sig_protocol, char chr);

/**
* This fuction allows you to stream in a set of keyboard scancodes and it
* will attempt to decode signatures and card swipes as the characters are
* passed in. To use this method be sure to implement your own EasyScriptEventListener
* and pass it to ::scriptel_add_event_listener() prior to passing characters to this function.
* This listener will be called when specific events are generated by decoding
* the stream.
* @param sig_protocol the protocol to use to interpret the data
* @param code the scancode of the next keyboard event to process
* @param shift 0 if the shift key was not down when the scancode was sent, non-zero if it was
*/
SCRIPTEL_SYMBOL_LINKAGE scriptel_return_status scriptel_keyboard_parse_keycode(const scriptel_signature_protocol* sig_protocol, int code, int shift);

/**
 * This method attempts to get the name of a financial card issuer by
 * enumeration member.
 * @param vendor Enumeration member pointing to card issuer.
 * @return Pointer to the name of the card issuer.
 */
SCRIPTEL_SYMBOL_LINKAGE const char* scriptel_get_card_issuer_name(scriptel_financial_card_vendor vendor);

/**
 * This function returns the most recent error generated by this library.
 * @return Most recent error in human readable format.
 */
SCRIPTEL_SYMBOL_LINKAGE char* scriptel_get_last_error();

/**
 * This function is a convinence function used to print out the contents of
 * a signature structure.
 * @param signature Signature to print.
 */
SCRIPTEL_SYMBOL_LINKAGE void scriptel_print_signature(scriptel_signature* signature);

/**
 * This function will free all allocated members inside of a signature
 * structure. It does not free the signature structure itself. Do not attempt
 * to use the structure after freeing it.
 * @param signature Signature to free.
 */
SCRIPTEL_SYMBOL_LINKAGE void scriptel_free_signature(scriptel_signature* signature);

/**
 * This function will free a scriptel_meta_data structure and all members inside of it.
 * @param meta data to be freed.
*/
SCRIPTEL_SYMBOL_LINKAGE void scriptel_free_cardswipe(scriptel_cardswipe* swipe);

/**
 * This function is a convinence function used to print out the contents of a
 * card swipe structure.
 * @param swipe Card swipe to print.
 */
SCRIPTEL_SYMBOL_LINKAGE void scriptel_print_cardswipe(scriptel_cardswipe* swipe);

/**
 * This function adds an event listener function. The functions added to this list will be 
 * called when an event occurs. If an event handler is added more than once, it will be
 * called more than once.
 * @param event_listener a function that takes as a parameter a pointer to a streaming_data union.
 */
SCRIPTEL_SYMBOL_LINKAGE void scriptel_add_event_listener(void(*event_listener)(streaming_event_data *sd));

/**
 * Removes a listener previously added through scriptel_add_event_listener. If it was never added or was
 * previously removed, the call is ignored. If it was added more than once, it will have to be removed
 * more than once...this function only removes the first instance.
 * @param event_listener a pointer to a function that was previously added through scriptel_add_event_listener
 */
SCRIPTEL_SYMBOL_LINKAGE void scriptel_remove_event_listener(void(*event_listener)(streaming_event_data *sd));

/**
 * This function removes all event listeners.
 */

SCRIPTEL_SYMBOL_LINKAGE void scriptel_remove_all_event_listeners();
/**
 * When a function returns SCRIPTEL_RETR_ERROR this call can be made to get a human readable English string explaining the error.
 */
SCRIPTEL_SYMBOL_LINKAGE char * scriptel_get_last_error();

/**
 * Frees all memory that was allocated during calls. It is not really necessary to call this funcion.
 * Some memory is allocated once and is used statically. This function frees that memory. It will be 
 * reallocated, if needed, later. 
 */
SCRIPTEL_SYMBOL_LINKAGE void scriptel_free_memory();

#endif
