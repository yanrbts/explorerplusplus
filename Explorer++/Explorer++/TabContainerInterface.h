// Copyright (C) Explorer++ Project
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "Tab.h"
#include <boost/signals2.hpp>
#include <unordered_map>

typedef boost::signals2::signal<void(int tabId, BOOL switchToNewTab)> TabCreatedSignal;
typedef boost::signals2::signal<void(const Tab &tab)> TabSelectedSignal;
typedef boost::signals2::signal<void(const Tab &tab, Tab::PropertyType propertyType)> TabUpdatedSignal;
typedef boost::signals2::signal<void(int tabId)> TabRemovedSignal;

typedef boost::signals2::signal<void(const Tab &tab)> NavigationCompletedSignal;

// Eventually, this will be driven by a dedicated class, rather than the
// Explorerplusplus class.
__interface TabContainerInterface
{
	/* TODO: Ideally, there would be a method of iterating over the tabs
	without having access to the underlying container. */
	const std::unordered_map<int, Tab>	&GetAllTabs() const;

	Tab				&GetTab(int tabId);
	Tab				*GetTabOptional(int tabId);
	Tab				&GetSelectedTab();
	Tab				&GetTabByIndex(int index);
	int				GetTabIndex(const Tab &tab);
	int				GetSelectedTabId() const;
	int				GetSelectedTabIndex() const;
	bool			IsTabSelected(const Tab &tab);
	void			SelectTab(const Tab &tab);
	int				MoveTab(const Tab &tab, int newIndex);
	void			DuplicateTab(const Tab &tab);
	int				GetNumTabs() const;
	bool			CloseTab(const Tab &tab);

	HRESULT			CreateNewTab(const TCHAR *TabDirectory, const TabSettings &tabSettings = {}, const FolderSettings *folderSettings = nullptr, const InitialColumns *initialColumns = nullptr, int *newTabId = nullptr);
	HRESULT			CreateNewTab(LPCITEMIDLIST pidlDirectory, const TabSettings &tabSettings = {}, const FolderSettings *folderSettings = nullptr, const InitialColumns *initialColumns = nullptr, int *newTabId = nullptr);
	FolderSettings	GetDefaultFolderSettings(LPCITEMIDLIST pidlDirectory) const;

	HRESULT			BrowseFolderInCurrentTab(const TCHAR *szPath, UINT wFlags);
	HRESULT			BrowseFolder(Tab &tab, const TCHAR *szPath, UINT wFlags);
	HRESULT			BrowseFolderInCurrentTab(LPCITEMIDLIST pidlDirectory, UINT wFlags);
	HRESULT			BrowseFolder(Tab &tab, LPCITEMIDLIST pidlDirectory, UINT wFlags);

	boost::signals2::connection	AddTabCreatedObserver(const TabCreatedSignal::slot_type &observer);
	boost::signals2::connection	AddTabSelectedObserver(const TabSelectedSignal::slot_type &observer);
	boost::signals2::connection	AddTabUpdatedObserver(const TabUpdatedSignal::slot_type &observer);
	boost::signals2::connection	AddTabRemovedObserver(const TabRemovedSignal::slot_type &observer);

	boost::signals2::connection	AddNavigationCompletedObserver(const NavigationCompletedSignal::slot_type &observer);
};