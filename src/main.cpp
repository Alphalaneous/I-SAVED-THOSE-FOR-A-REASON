#include <Geode/Geode.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {

    void FLAlert_Clicked(FLAlertLayer* alert, bool confirmed) {
		if (alert->getTag() == 1) {
			if (!confirmed) return;

			GameLevelManager* levelManager = GameLevelManager::get();

			SearchType searchFilter = SearchType::Search;
			if (m_searchObject) {
				searchFilter = m_searchObject->m_searchType;
			}

			CCArray* savedLevels = levelManager->getSavedLevels(false, m_searchObject->m_folder);

			if (m_searchObject && m_searchObject->m_folder != 0) {
				std::string searchQuery = m_searchObject->m_searchQuery;
				if (!searchQuery.empty()) {
					savedLevels = getItemsMatchingSearch(savedLevels, searchQuery, m_searchObject);
				}
			}

			for (GJGameLevel* level : CCArrayExt<GJGameLevel*>(savedLevels)) {
				if (m_searchObject->m_folder == level->m_levelFolder && !level->m_levelFavorited) {
					levelManager->deleteLevel(level);
				}
			}

			onSaved(this);
			MusicDownloadManager::sharedState()->clearUnusedSongs();
			return;
		}
		LevelBrowserLayer::FLAlert_Clicked(alert, confirmed);
	}
};