# Audio player
Reference implementation of the simplest possible audio player.

Plays one selected audio file in an endless loop until closed or paused or something else is selected.

`QSettings` used for remembering volume and path to the last played file.

`Custom context menu` used for displaying options for selecting file and pausing/resuming.

`Volume` is at linear scale.

No `dynamic memory` is used directly.

Depends on system codecs.

# Possible improvements
1. Use logatithmic scale for volume
2. Test
3. Translate
4. Remove code from `MainWindow`
5. Make better volume control (`QSpinBox` doesn't reset focus properly)
