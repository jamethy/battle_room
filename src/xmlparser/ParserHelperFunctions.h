#ifndef PARSERFUNCIONS_H
#define PARSERFUNCIONS_H

#include <string>
#include <unordered_map>

namespace XmlParser {

/*!
 * Reads an entire text file into a string.
 * \param filename Name of file to read in.
 * \return Entire file or emtpy string if file not found.
 */
std::string readEntireFile(const std::string& filename);

/*!
 * Returns a string with all '\n' characters removed from the input.
 * \param str String to remove the line endings from.
 * \return Copy of str without '\n' characters.
 */
std::string removeAllLineEndings(std::string str);

/*!
 * Returns a string with all XML comments removed - they look like <!-- ... -->
 * Assumes string is one line - use removeAllLineEndings
 * \param str String to remove the comments from.
 * \return Copy of str without xml comments.
 */
std::string removeAllComments(const std::string& str);

/*!
 * Returns a string with all the XML self-enclosed tags expanded.
 * Example input: <Head name="hello" />
 * Example output: <Head name="hello" ></Head>
 * Note it assumes string is one line - use removeAllLineEndings
 * \param str String to expand all the tags in
 * \return Copy of str with all tags expanded
 */
std::string expandAllSelfenclosed(const std::string& str);

/*!
 * Returns a map of the attribute pairs in attribute_set. Note they look
 * something like: attribute="attribute value"
 * \param attribute_set String containing a list of attribute pairs
 * \return Map containing paris of attributes and values
 */
std::unordered_map<std::string,std::string> 
parseAttributes(const std::string& attribute_set);

/*!
 * Filters str using the above functions so it is ready to be parsed by XmlItem.
 * It will do filters such as removing line endings, comments, and expand tags.
 * \param str Raw xml string.
 * \return Copy of str that has been filtered.
 */
std::string filterXmlString(const std::string& str);

} // XmlParser namespace

#endif // PARSERFUNCIONS_H
