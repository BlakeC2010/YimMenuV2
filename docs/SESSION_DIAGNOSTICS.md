# Session connection diagnostics

This branch adds diagnostic log messages to help locate **where** a session join fails.
It does not bypass BattlEye, modify matchmaking or network packets, or guarantee access to protected sessions.

## Reproducing a problem

1. Back up local FSL saves before changing any game files or settings.
2. Note the current GTA Enhanced build, YimMenu build, and FSL version.
3. In the menu, note whether **Network > Enhancements > Fast Join** or **Force Script Host** is enabled. Both features warn about possible job/mission problems; test with both disabled.
4. Note whether **Join YimMenu-only Sessions** and the matchmaking spoofing options are enabled.
5. Attempt one connection. Record the time, whether the attempt used YimMenu's **Join** or the game's normal friend invitation, and the exact error text.
6. Inspect `%APPDATA%\YimMenuV2\cout.log` for `[SessionDiag]` around that time.

For a control test, fully close the game, disable YimMenu and FSL (retain a backup of FSL files), enable BattlEye, and attempt to join the same friend's normal invite-only session. FSL stores local progress separately; missing FSL progress during the control test is expected.

## Interpreting the new messages

| Message | Meaning |
| --- | --- |
| `Session-type join requested` | YimMenu requested a join type; there is no confirmation of success yet. |
| `Requesting session information for a player` | A RID-based session query started. The ID is not logged. |
| `Session-info lookup completed` | The query returned a status and an error code. |
| `Session-info join blocked` | A transition or player switch was already underway. |
| `Queuing session-info join` | A request was queued for the game's transition script. |
| `Attempting queued session-info join` | The hook invoked the join request. |
| `Session-info join request was rejected immediately` | The local join function returned false. |
| `Session-info join request accepted` | The local join function returned true; **it does not prove a session connection was established**. |
| `Network player manager shutdown observed` | A local shutdown occurred. This also happens during normal session transitions; **it is not a disconnect reason**. |

Not every joining method goes through `JoinSessionInfo`. For example, a normal in-game friend invite may produce no join-request lines; the shutdown entry is still a useful timing marker if it occurs.

## Limitations

The log cannot reliably identify why a remote host removed a player, nor can it establish an anti-cheat verdict. YimMenu upstream documents that BattlEye-disabled clients may be disconnected by protected hosts when required checks fail. No session-log instrumentation can change that restriction.

The log may contain personal or session-related information from unrelated subsystems. Review and redact usernames, IDs, tokens and other identifiers before sharing it publicly.
