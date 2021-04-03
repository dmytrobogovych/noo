The idea is to keep server simple as much as possible.

This will serve as central endpoint to provide API.

- list all available devices for the user.
- list all upcoming changes starting from given datetime excluding some device(s).
- put new change to backend.

Type of changes:

- import: initial import of texts
- text diff
- branch operation - add / delete / move / rename
- new time intervals
- delete time intervals

All data is encrypted. Server hasn't access to changes content. Changes are treated as BLOBs.

