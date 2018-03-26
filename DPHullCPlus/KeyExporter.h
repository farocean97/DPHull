/* ****************************************************************************
 *
 * Copyright (c) Microsoft Corporation. 
 *
 * This source code is subject to terms and conditions of the Microsoft Public License. A 
 * copy of the license can be found in the License.html file at the root of this distribution. If 
 * you cannot locate the  Microsoft Public License, please send an email to 
 * dlr@microsoft.com. By using this source code in any fashion, you are agreeing to be bound 
 * by the terms of the Microsoft Public License.
 *
 * You must not remove this notice, or any other, from this software.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 * ***************************************************************************/
#if !defined(AFX_TKEYEXPORTER_H__F779C9D6_C433_4043_A8BB_CE2D10EC1F88__INCLUDED_)
#define AFX_TKEYEXPORTER_H__F779C9D6_C433_4043_A8BB_CE2D10EC1F88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "LineApproximator.h"

namespace hull
{
/*
template <class T, class TPointContainer, class>
class TKeyVectorExporter : virtual public TLine<T, TPointContainer, TKeyContainer>  
{
public:
	//! \name Accessing data
	//@{
	//! fill vectors with keys
	void GetKeyToVector( std::vector<T>& vX, std::vector<T>& vY)
	{
		vX=m_vKeyX;
		vY=m_vKeyY;
	}
	//! return reference to vector of key x coordinates
	const TVector& GetKeyX() const		{	return m_vKeyX;};
	//! return reference to vector of key y coordinates
	const TVector& GetKeyY() const		{	return m_vKeyY;};
	//@}

protected:
	//! fill vectors with results
	virtual void ExportKeys();
private:
	TVector m_vKeyX;
	TVector m_vKeyY;
};

template<class T, class TPointContainer>
void TKeyVectorExporter<T,TPointContainer>::ExportKeys()
{
	const KeyContainer& kc=GetKeys();
	KeyContainer::const_iterator it;
	UINT i;

	m_vKeyX.resize(kc.size());
	m_vKeyY.resize(kc.size());

	for (it=kc.begin(), i=0; it!= kc.end();it++, i++)
	{
		m_vKeyX[i]=(*it)->x;
		m_vKeyY[i]=(*it)->y;
	}
}

template <class T,class TPointContainer>
class TKeyVectorPointerExporter : virtual public TLine<T,TPointContainer>  
{
public:
	//! \name Constructor
	//@{
	//! Constructor
	TKeyVectorPointerExporter( TVector* pX =NULL, TVector* pY=NULL): m_pKeyX(pX), m_pKeyY(pY){};
	//@}

	//! \name Accessing data
	//@{
	void SetKeyPointers( TVector* pX, TVector* pY)			{	m_pKeyX = pX; m_pKeyY=pY;};
	//! return reference to vector of key x coordinates, const
	const TVector* GetKeyX() const		{	return m_pKeyX;};
	//! return reference to vector of key y coordinates, const
	const TVector* GetKeyY() const		{	return m_pKeyY;};
	//! return reference to vector of key x coordinates
	TVector* GetKeyX()					{	return m_pKeyX;};
	//! return reference to vector of key y coordinates
	TVector* GetKeyY()					{	return m_pKeyY;};
	//@}

protected:
	//! fill vectors with results
	virtual void ExportKeys();
private:
	TVector* m_pKeyX;
	TVector* m_pKeyY;
};

template<class T,class TPointContainer>
void TKeyVectorPointerExporter<T,TPointContainer>::ExportKeys()
{
	const KeyContainer& kc=GetKeys();
	KeyContainer::const_iterator it;
	UINT i;

	if (!m_pKeyX || !m_pKeyY)
		return;

	m_pKeyX->resize(kc.size());
	m_pKeyY->resize(kc.size());

	for (it=kc.begin(), i=0; it!= kc.end();it++, i++)
	{
		(*m_pKeyX)[i]=(*it)->x;
		(*m_pKeyY)[i]=(*it)->y;
	}
}
*/
};

#endif // !defined(AFX_TKEYEXPORTER_H__F779C9D6_C433_4043_A8BB_CE2D10EC1F88__INCLUDED_)