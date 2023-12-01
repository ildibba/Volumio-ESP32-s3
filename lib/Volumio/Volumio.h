/*#################################################################*\

Copyright 2020 Jakob Föger

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

\*#################################################################*/

#include "SocketIO.h"
#include "VolumioStructs.h"

class Volumio
{

public:
  enum PushType
  {
    pushNone,
    pushState,
    pushBrowseSources,
    pushQueue,
    pushBrowseLibrary,
    pushToastMessage,
    pushMultiRoomDevices,
    pushUiSettings,
    pushDeviceInfo,
    pushSystemVersion,
    pushAvailableLanguages,
    pushAudioOutputs,
    pushMenuItems,
    pushUiConfig,
    pushInstalledPlugins,
    pushAvailablePlugins,
    pushUnknown
  };

  //Pushed states
  StateStruct State;
  SourceStruct CurrentSourceItem;
  LibraryItemStruct CurrentLibraryItem;
  LibraryInfoStruct LibraryInfo;
  LibraryPrevStruct LibraryPrev;
  QueueItemStruct CurrentQueueItem;
  ToastStruct CurrentToastItem;
  MultroomDeviceStruct CurrentMultiRoomDevice;
  UiSettingsStruct UiSettings;
  DeviceInfoStruct DeviceInfo;
  SystemVersionStruct SystemVersion;
  MenuItemStruct CurrentMenuItem;
  UiConfigSectionStruct CurrentUiConfigSection;
  UiConfigContentStruct CurrentUiConfigContent;
  InstalledPluginStruct CurrentInstalledPlugin;
  //AvailablePluginStruct CurrentAvailablePlugin;

  //New State received
  PushType getPushType() { return pushType; };

  //Call oce in Setup
  void connect(String hostname, int portnr);
  bool getConnected();

  //Call cyclic in loop()
  void process();

  bool readNextSourceItem();
  bool readNextLibraryItem();
  bool readNextQueueItem();
  bool readLibraryPrev();
  bool readPushToastMessage();
  bool readState();
  bool readMultiRoomDevice();
  bool readUiSettings();
  bool readDeviceInfo();
  bool readSystemVersion();
  bool readNextMenuItem();
  bool readNextUiConfigSection();
  bool readNextUiConfigContent();
  bool readNextInstalledPlugin();
  bool readNextAvailablePlugin();

  //Commands
  void getState();
  void getQueue();
  void removeQueueItem(int index);
  void addToQueue(String uri);
  void addToQueue(String service, String title, String uri);
  void replaceAndPlay(String uri);
  void replaceAndPlay(String service, String title, String uri);
  void addPlay(String uri);
  void addPlay(String service, String name, String uri);
  
  void addToFavourites(String service, String title, String uri);

  void seek(int position);
  void getBrowseSources();
  void browseLibrary(String uri);
  void play();
  void play(int index);
  void volatilePlay();
  void pause();
  void toggle();
  void stop();
  void clearQueue();
  void prev();
  void next();
  void setRandom(bool flag);
  void setRepeat(bool flag);
  void volume(int volume);
  void mute();
  void unmute();

  void getDeviceInfo();
  void getSystemVersion();
  void getAudioOutputs();
  void getUiSettings();
  void getAvailableLanguages();
  void getPlaylistIndex();
  void getMenuItems();

  void getUiConfig(String page);

  void getInstalledPlugins();
  void getAvaliablePlugins();

private:
  PushType pushType = pushNone;
  SocketIO socketIoClient;
  JSON jsonParser;
  unsigned long lastTime = 0;
};
