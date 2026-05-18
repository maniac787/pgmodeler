v2.0.0-beta
------
*Release date: May 20, 2026*
*Changes since:* ***v2.0.0-alpha1***

**Summary:** pgModeler 2.0.0-beta continues the path opened by the previous alpha releases, bringing a focused set of improvements aimed at everyday usability, visual consistency, and application stability. This release introduces protections against accidental data loss, a fully customizable interface font, significant improvements to the SQL results experience, better diagnostics on crashes, and a clean separation between the Community and Plus Edition builds. Alongside these new capabilities, a number of important bugs have been fixed, making this the most advanced pre-release version of pgModeler 2.0 so far.

**Accidental data loss prevention:** When editing any database object, if you make changes and accidentally press Escape to close the form, pgModeler now detects unsaved modifications and asks for your confirmation before discarding them. This simple safeguard prevents frustrating accidents that could otherwise require re-entering complex configurations from scratch.

**Personalized interface font:** You can now choose any font installed on your system as the application's UI font directly from the Appearance Settings. pgModeler ships with the Exo 2 font as its new built-in default, giving the interface a clean and modern look. Your font preferences are saved and applied after a restart. The canvas object labels have also been updated to use the Montserrat font family for a more refined and readable appearance.

**Refreshed visual identity:** Application icons, logos and the splash screen have been updated across all platforms with a more polished and consistent design. Popup menus in the inksaver, light and dark themes now have a cohesive styled appearance with proper borders and separators. 

**SQL results made easier:** Working with large query result sets is now more comfortable. Result loading can be cancelled at any time, and a progress indicator is shown while data is being loaded. A new context menu on the results grid offers quick actions to select all rows, auto-fit column widths, or auto-fit row heights. For very large result sets — over 10,000 rows — pgModeler warns before attempting a full resize, preventing the interface from freezing on oversized data.

**Better encoding awareness:** The server's character encoding is now displayed in the connection testing dialog and in the SQL execution and data management panels. This helps identify potential encoding incompatibilities before they turn into errors during database management sessions.

**Crash diagnostics in CLI:** When pgModeler command-line interface crashes unexpectedly, the application now captures a detailed diagnostic report and dumps it on screen. This includes human-readable information on Linux and macOS, with basic support on Windows. These reports make it significantly easier to investigate and report bugs.

**Data grid improvements:** The data grid now offers an option to skip conflicting rows silently when inserting data, allowing bulk inserts to continue without failing the entire operation when a conflict is encountered.

**Smarter file dialogs:** File save dialogs now always append the correct file extension automatically, and the extension updates as you switch between available file type filters — no more accidentally saving files without an extension. Recent files in the File menu now display the full file path in the tooltip, making it easy to distinguish between models with the same filename stored in different folders.

**Plugin API improvements:** Plugins now have more control over where their interface elements appear. They can add panels to the main window side bar, to the SQL execution area, or choose not to dock any panel at all. Plugins can also integrate buttons directly into the welcome screen, providing a more native and integrated experience.

**Community and Plus Edition clarity:** The legacy demo mode has been removed entirely from the codebase. pgModeler is now cleanly split between the Community Edition (open source) and pgModeler Plus (commercial), with no hidden restrictions left in the community build.

**Breaking change — LATIN1 database compatibility:** If you work with PostgreSQL databases using the LATIN1 character encoding, please note that an internal separator character was changed to ensure compatibility with that encoding. This resolves errors that were previously triggered when performing diff or import operations against LATIN1-encoded databases. Models created in previous version may need to be fixed via pgmodeler-cli in case of load problems.

**Bug fixes and stability:** Several important bugs have been fixed in this release. A crash that occurred when closing the application after a diff operation has been resolved. Model validation now correctly identifies broken references to types provided by PostgreSQL extensions. Discarding changes in the Settings window no longer leaves the connection configuration in an inconsistent state. Newly opened models are now correctly appended to the navigation history instead of being inserted in the wrong position. The import results button in the SQL tool is no longer enabled when a query returns no rows, which previously caused a crash. Finally, several issues with the custom interface font not rendering correctly on macOS and Windows have been resolved.

**Looking ahead:** With 2.0.0-beta, pgModeler enters a stable pre-release state. The focus for the final 2.0.0 release will be on polishing remaining rough edges, addressing community feedback, and ensuring solid stability across all supported platforms. Thank you for your continued support and for helping shape the future of pgModeler.



