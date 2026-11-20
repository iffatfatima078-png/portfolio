import React, { useMemo, useState } from 'react';
import {
  View,
  Text,
  FlatList,
  TextInput,
  Pressable,
  Modal,
  ScrollView,
  StatusBar,
  StyleSheet,
  Platform,
  Linking,
  SafeAreaView,
} from 'react-native';

/* -------------------------------------------------------------------------
   1. YOUR DATA  (edit this list by hand to add or change sales)
   - brand:    which brand has the sale
   - item:     which thing is on sale
   - discount: percent off
   - ends:     last day of the sale, format YYYY-MM-DD
   - link:     optional, the brand's sale page
   The rows below are SAMPLE data so the app has something to show.
   Replace them with real sales you find on Google or the brands' websites.
   ------------------------------------------------------------------------- */
const DAY = 24 * 60 * 60 * 1000;
const inDays = (n) => new Date(Date.now() + n * DAY).toISOString().slice(0, 10);

const SALES = [
  { id: '1', brand: 'Khaadi', category: 'Clothes', item: 'Unstitched lawn 3-piece', discount: 30, ends: inDays(4), note: 'Online and in stores.', link: 'https://pk.khaadi.com' },
  { id: '2', brand: 'Sapphire', category: 'Clothes', item: 'Ready-to-wear kurtas', discount: 40, ends: inDays(9), note: 'Selected styles only.', link: 'https://pk.sapphireonline.pk' },
  { id: '3', brand: 'Nike', category: 'Shoes', item: 'Running shoes', discount: 25, ends: inDays(2), note: 'While stock lasts.', link: '' },
  { id: '4', brand: 'Bata', category: 'Shoes', item: 'Casual sandals', discount: 50, ends: inDays(14), note: 'Buy one, get the second at half price.', link: '' },
  { id: '5', brand: 'Outfitters', category: 'Clothes', item: "Men's denim jeans", discount: 35, ends: inDays(6), note: '', link: '' },
  { id: '6', brand: 'Servis', category: 'Shoes', item: 'School shoes', discount: 20, ends: inDays(1), note: 'Last day tomorrow.', link: '' },
  { id: '7', brand: 'Gul Ahmed', category: 'Clothes', item: 'Winter shawls', discount: 45, ends: inDays(11), note: '', link: '' },
];

/* -------------------------------------------------------------------------
   2. HELPERS
   ------------------------------------------------------------------------- */
const daysLeft = (ends) =>
  Math.ceil((new Date(ends + 'T23:59:59').getTime() - Date.now()) / DAY);

const endsLabel = (d) => {
  if (d <= 0) return 'Ends today';
  if (d === 1) return '1 day left';
  return `${d} days left`;
};

const CATEGORIES = ['All', ...Array.from(new Set(SALES.map((s) => s.category)))];

const COLORS = {
  bg: '#F2F4F7',
  card: '#FFFFFF',
  ink: '#101828',
  muted: '#667085',
  green: '#0B6E4F',
  greenSoft: '#DDF1E9',
  tag: '#FFB400',
  urgent: '#C2410C',
  line: '#E4E7EC',
};

/* -------------------------------------------------------------------------
   3. SCREENS / COMPONENTS
   ------------------------------------------------------------------------- */
function SaleCard({ sale, onPress }) {
  const d = daysLeft(sale.ends);
  const urgent = d <= 2;
  return (
    <Pressable
      onPress={onPress}
      style={({ pressed }) => [styles.card, pressed && { opacity: 0.85 }]}
      accessibilityRole="button"
      accessibilityLabel={`${sale.brand}, ${sale.item}, ${sale.discount} percent off`}
    >
      <View style={{ flex: 1, paddingRight: 12 }}>
        <Text style={styles.brand}>{sale.brand}</Text>
        <Text style={styles.item}>{sale.item}</Text>
        <Text style={[styles.meta, urgent && { color: COLORS.urgent, fontWeight: '700' }]}>
          {endsLabel(d)}
        </Text>
      </View>
      <View style={styles.tag}>
        <Text style={styles.tagNumber}>{sale.discount}%</Text>
        <Text style={styles.tagOff}>off</Text>
      </View>
    </Pressable>
  );
}

function DetailModal({ sale, onClose }) {
  if (!sale) return null;
  const d = daysLeft(sale.ends);
  return (
    <Modal animationType="slide" transparent onRequestClose={onClose} visible>
      <Pressable style={styles.backdrop} onPress={onClose} />
      <View style={styles.sheet}>
        <View style={styles.grab} />
        <Text style={styles.sheetBrand}>{sale.brand}</Text>
        <Text style={styles.sheetItem}>{sale.item}</Text>

        <View style={styles.sheetRow}>
          <View style={styles.tagLarge}>
            <Text style={styles.tagLargeText}>{sale.discount}% off</Text>
          </View>
          <Text style={styles.sheetCategory}>{sale.category}</Text>
        </View>

        <Text style={styles.sheetLine}>Sale ends: {sale.ends} ({endsLabel(d)})</Text>
        {!!sale.note && <Text style={styles.sheetLine}>{sale.note}</Text>}

        {!!sale.link && (
          <Pressable style={styles.primaryBtn} onPress={() => Linking.openURL(sale.link)}>
            <Text style={styles.primaryBtnText}>Open brand website</Text>
          </Pressable>
        )}
        <Pressable style={styles.secondaryBtn} onPress={onClose}>
          <Text style={styles.secondaryBtnText}>Close</Text>
        </Pressable>
      </View>
    </Modal>
  );
}

export default function App() {
  const [query, setQuery] = useState('');
  const [category, setCategory] = useState('All');
  const [sortBy, setSortBy] = useState('ending'); // 'ending' | 'discount'
  const [selected, setSelected] = useState(null);

  const data = useMemo(() => {
    const q = query.trim().toLowerCase();
    return SALES.filter((s) => daysLeft(s.ends) >= 0) // hide finished sales
      .filter((s) => category === 'All' || s.category === category)
      .filter(
        (s) => !q || s.brand.toLowerCase().includes(q) || s.item.toLowerCase().includes(q)
      )
      .sort((a, b) =>
        sortBy === 'discount' ? b.discount - a.discount : daysLeft(a.ends) - daysLeft(b.ends)
      );
  }, [query, category, sortBy]);

  return (
    <SafeAreaView style={styles.safe}>
      <StatusBar barStyle="dark-content" backgroundColor={COLORS.bg} />

      <View style={styles.header}>
        <Text style={styles.title}>Sale Alert</Text>
        <Text style={styles.subtitle}>
          {data.length} {data.length === 1 ? 'brand has' : 'brands have'} a sale right now
        </Text>
      </View>

      <TextInput
        style={styles.search}
        placeholder="Search a brand or item"
        placeholderTextColor={COLORS.muted}
        value={query}
        onChangeText={setQuery}
        autoCorrect={false}
        returnKeyType="search"
      />

      <View>
        <ScrollView
          horizontal
          showsHorizontalScrollIndicator={false}
          contentContainerStyle={styles.chipRow}
        >
          {CATEGORIES.map((c) => {
            const active = c === category;
            return (
              <Pressable
                key={c}
                onPress={() => setCategory(c)}
                style={[styles.chip, active && styles.chipActive]}
              >
                <Text style={[styles.chipText, active && styles.chipTextActive]}>{c}</Text>
              </Pressable>
            );
          })}
        </ScrollView>
      </View>

      <View style={styles.sortRow}>
        <Text style={styles.sortLabel}>Sort by</Text>
        {[
          ['ending', 'Ending soon'],
          ['discount', 'Biggest discount'],
        ].map(([key, label]) => (
          <Pressable key={key} onPress={() => setSortBy(key)}>
            <Text style={[styles.sortOption, sortBy === key && styles.sortOptionActive]}>
              {label}
            </Text>
          </Pressable>
        ))}
      </View>

      <FlatList
        data={data}
        keyExtractor={(s) => s.id}
        contentContainerStyle={{ padding: 16, paddingTop: 4 }}
        renderItem={({ item }) => <SaleCard sale={item} onPress={() => setSelected(item)} />}
        ListEmptyComponent={
          <Text style={styles.empty}>No sales match. Try another brand or category.</Text>
        }
      />

      <DetailModal sale={selected} onClose={() => setSelected(null)} />
    </SafeAreaView>
  );
}

/* -------------------------------------------------------------------------
   4. STYLES
   ------------------------------------------------------------------------- */
const styles = StyleSheet.create({
  safe: {
    flex: 1,
    backgroundColor: COLORS.bg,
    paddingTop: Platform.OS === 'android' ? StatusBar.currentHeight || 0 : 0,
  },
  header: { paddingHorizontal: 16, paddingTop: 12, paddingBottom: 8 },
  title: { fontSize: 30, fontWeight: '800', color: COLORS.green, letterSpacing: -0.5 },
  subtitle: { fontSize: 14, color: COLORS.muted, marginTop: 2 },

  search: {
    marginHorizontal: 16,
    marginVertical: 8,
    backgroundColor: COLORS.card,
    borderRadius: 12,
    borderWidth: 1,
    borderColor: COLORS.line,
    paddingHorizontal: 14,
    paddingVertical: Platform.OS === 'ios' ? 12 : 8,
    fontSize: 15,
    color: COLORS.ink,
  },

  chipRow: { paddingHorizontal: 16, paddingVertical: 6 },
  chip: {
    paddingHorizontal: 14,
    paddingVertical: 8,
    borderRadius: 20,
    backgroundColor: COLORS.card,
    borderWidth: 1,
    borderColor: COLORS.line,
    marginRight: 8,
  },
  chipActive: { backgroundColor: COLORS.green, borderColor: COLORS.green },
  chipText: { color: COLORS.ink, fontSize: 14, fontWeight: '600' },
  chipTextActive: { color: '#FFFFFF' },

  sortRow: { flexDirection: 'row', alignItems: 'center', paddingHorizontal: 16, paddingVertical: 8 },
  sortLabel: { color: COLORS.muted, fontSize: 13, marginRight: 12 },
  sortOption: { color: COLORS.muted, fontSize: 13, marginRight: 14, paddingVertical: 4 },
  sortOptionActive: { color: COLORS.green, fontWeight: '700', textDecorationLine: 'underline' },

  card: {
    flexDirection: 'row',
    alignItems: 'center',
    backgroundColor: COLORS.card,
    borderRadius: 14,
    padding: 16,
    marginBottom: 10,
    borderLeftWidth: 5,
    borderLeftColor: COLORS.green,
  },
  brand: { fontSize: 19, fontWeight: '800', color: COLORS.ink },
  item: { fontSize: 15, color: COLORS.ink, marginTop: 2 },
  meta: { fontSize: 13, color: COLORS.muted, marginTop: 6 },

  tag: {
    backgroundColor: COLORS.tag,
    borderRadius: 10,
    paddingVertical: 8,
    paddingHorizontal: 12,
    alignItems: 'center',
    minWidth: 68,
  },
  tagNumber: { fontSize: 22, fontWeight: '900', color: COLORS.ink },
  tagOff: { fontSize: 12, fontWeight: '700', color: COLORS.ink, marginTop: -2 },

  empty: { textAlign: 'center', color: COLORS.muted, marginTop: 48, fontSize: 15 },

  backdrop: { flex: 1, backgroundColor: 'rgba(16,24,40,0.45)' },
  sheet: {
    backgroundColor: COLORS.card,
    padding: 20,
    paddingBottom: 32,
    borderTopLeftRadius: 24,
    borderTopRightRadius: 24,
  },
  grab: {
    alignSelf: 'center',
    width: 40,
    height: 4,
    borderRadius: 2,
    backgroundColor: COLORS.line,
    marginBottom: 16,
  },
  sheetBrand: { fontSize: 26, fontWeight: '800', color: COLORS.ink },
  sheetItem: { fontSize: 17, color: COLORS.ink, marginTop: 4 },
  sheetRow: { flexDirection: 'row', alignItems: 'center', marginVertical: 14 },
  tagLarge: { backgroundColor: COLORS.tag, borderRadius: 8, paddingHorizontal: 12, paddingVertical: 6 },
  tagLargeText: { fontSize: 18, fontWeight: '900', color: COLORS.ink },
  sheetCategory: {
    marginLeft: 12,
    color: COLORS.green,
    backgroundColor: COLORS.greenSoft,
    paddingHorizontal: 10,
    paddingVertical: 4,
    borderRadius: 8,
    overflow: 'hidden',
    fontWeight: '700',
    fontSize: 13,
  },
  sheetLine: { fontSize: 15, color: COLORS.muted, marginBottom: 6 },
  primaryBtn: {
    backgroundColor: COLORS.green,
    borderRadius: 12,
    paddingVertical: 14,
    alignItems: 'center',
    marginTop: 16,
  },
  primaryBtnText: { color: '#FFFFFF', fontSize: 16, fontWeight: '700' },
  secondaryBtn: { paddingVertical: 14, alignItems: 'center', marginTop: 4 },
  secondaryBtnText: { color: COLORS.muted, fontSize: 15, fontWeight: '600' },
});