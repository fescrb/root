/*
 * Copyright (C) 2020  Fernando Escribano Macias 
 *
 * This file is part of the Root Engine.
 * 
 * The Root Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Root Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with The Root Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <root/io/stream.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace root {

class aasset_stream final : public stream {
public:
    explicit aasset_stream(AAsset *asset);
    //aasset_stream(AAssetManager *manager, const char* filename);
    //aasset_stream(AAssetManager *manager, string filename);

    u64 read(buffer* dst) override;
    i64 seek(const i64& offset, const stream::offset_relativity& offset_relativity) override;
    u64 remaining() override;
    u64 length() override;

    virtual ~aasset_stream();

private:
    AAsset* m_asset;
};

} // namespace root